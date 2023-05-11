#!/usr/local/bin/python3
"""
Script to convert an XML file from a standard YIN schema to the schema used
by the M-Plane server application's YangConfig.xml file. It uses an input
YANG model file to identify each node type. The script can be run multiple
times with different YANG model files to handle imported nodes.
"""
import sys
import os.path
import re
from pathlib import Path

if len(sys.argv) != 4:
    print(
        "Usage: convert_xml_formats.py <yang model file> <xml file to convert> <output file>"
    )
    quit()

yang_file = sys.argv[1]
xml_file = sys.argv[2]
out_file = sys.argv[3]

container_p = re.compile("container (.*){")
leaf_p = re.compile("leaf (.*){")
list_p = re.compile("^(?!leaf-)list (.*){")
leaf_list_p = re.compile("leaf-list (.*){")

containers = set()
leaves = set()
lists = set()
leaf_lists = set()

with open(yang_file) as f:
    # spaces in YANG are only required to separate tokens; this assumes the YANG
    # file has been formatted with one data definition statment per line
    # (as O-RAN YANG files are)
    lines = f.readlines()
    for line in lines:
        line = line.strip()
        m = container_p.match(line)
        if m is not None:
            containers.add(m.group(1).strip())
        m = leaf_p.match(line)
        if m is not None:
            leaves.add(m.group(1).strip())
        m = list_p.match(line)
        if m is not None:
            lists.add(m.group(1).strip())
        m = leaf_list_p.match(line)
        if m is not None:
            leaf_lists.add(m.group(1).strip())

txt = Path(xml_file).read_text()

# remove comments for moving <listEntry>s and listLeaf <entry>s into same node
txt = re.sub(r"(?m)^[ \t]*<!--.*-->\n?", "", txt)

# add "container-"
for container in containers:
    txt = re.sub(r"<{}>".format(container), r"<container-{}>".format(container), txt)
    txt = re.sub(r"</{}>".format(container), r"</container-{}>".format(container), txt)

# add "leaf-" and move values into "value="
for leaf in leaves:
    txt = re.sub(
        r"<{}>(.*)</{}>".format(leaf, leaf), r'<leaf-{} value="\1" />'.format(leaf), txt
    )

# add "list-", move each list entry into a <listEntry>
# then, move all <listEntry>s into same <list-
# TODO: try to indent listEntry properly?
for list_node in lists:
    txt = re.sub(
        r"([ \t]*)<{}>(.*?)</{}>".format(list_node, list_node),
        r"\1<list-{}>\n\1  <listEntry>\2  </listEntry>\n\1</list-{}>".format(
            list_node, list_node
        ),
        txt,
        flags=re.DOTALL,
    )
    txt = re.sub(
        r"([ \t]*)</list-{}>\n([ \t]*)<list-{}>\n".format(list_node, list_node), "", txt
    )

# add "listLeaf-" and move values into <entry value="
# then, move all <entry>s next to each other
for leaf_list in leaf_lists:
    txt = re.sub(
        r"([ \t]*)<{}>(.*?)</{}>".format(leaf_list, leaf_list),
        r'\1<listLeaf-{}>\n\1  <entry value="\2" />\n\1</listLeaf-{}>'.format(
            leaf_list, leaf_list
        ),
        txt,
        flags=re.DOTALL,
    )
    txt = re.sub(
        r"([ \t]*)</listLeaf-{}>\n([ \t]*)<listLeaf-{}>\n".format(leaf_list, leaf_list),
        "",
        txt,
    )

with open(out_file, "w") as out_f:
    out_f.write(txt)
