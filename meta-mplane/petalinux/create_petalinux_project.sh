#!/bin/bash -i

function usage () {
 echo "./create_petalinux_project.sh <BSP> <PROJECT>"
 echo ""
 echo "Create a Petalinux project for a target board"
 echo ""
 echo "Arguments:"
 echo "    BSP: Path to the BSP file used to generate the project."
 echo "    PROJECT: The project-spec to use."
}

# Validate args
BSP=$1
test -f "$BSP" || { echo "BSP not found" ; usage ; exit 1 ; }

shift
PROJECT=$1
test "$PROJECT" = "" || \
    test -d "project-specs/$PROJECT" || \
    { echo "Project spec $PROJECT not found" ; usage ; exit 1 ; }

shift

# Create project
petalinux-create -t project -n $PROJECT -s $BSP
cd $PROJECT

# Config
### Default Config
petalinux-config --silentconfig

### Add Installed SSTATE_MIRRORS
ln=$(cat -n build/conf/plnxtool.conf  | grep SSTATE_MIRRORS | cut -f 1) ; ln=$((ln+1)) ;
sed -i "${ln}i file://.* file:///opt/petalinux/2020.1/sstate-cache/PATH \\" build/conf/plnxtool.conf

### Add project-spec
if [[ "$PROJECT" != "" ]];
then
  rm -rf project-spec # Remove default project-spec folder
  PROJECT_SPEC_PATH="$MPLANE/meta-mplane/petalinux/project-specs/$PROJECT"
  cp -r $PROJECT_SPEC_PATH ./project-spec
fi
