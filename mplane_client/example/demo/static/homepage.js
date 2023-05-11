function init() {
    $('#alarms-table').bootstrapTable({
      "scrollY": "700px"
    });
    $("#alarms-table").bootstrapTable("hideLoading");
    
    
    var socket = io();
    socket.on("connect", function() {})
    socket.on("alarms", function(data) {
      alarms = JSON.parse(data["alarms"])
      console.log(alarms)
      $('#alarms-table').bootstrapTable('load', alarms)
    });
    function updateAlarms() {
      socket.emit("alarms")
    }
    setInterval(updateAlarms, 3000)
}
