const char PAGE_INDEX[] PROGMEM = R"=====(
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>416 Light Control</title>
    <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
    <link rel="stylesheet" href="https://code.getmdl.io/1.3.0/material.indigo-pink.min.css">
    <script defer src="https://code.getmdl.io/1.3.0/material.min.js"></script>
    
    <style type="text/css">
      body {
        font-family: monospace;
        background-color: #2f2f2f;
        color: white;
      }
      #container {
        max-width: 400px;
        margin: auto;
        padding: 0px 20px;
      }
      .card {
        background-color: #444;
        padding: 15px;
        overflow: auto;
        margin: 10px 0px;
        border-radius: 10px;
      }
      .text {
        font-size: 20px;
        float: right;
      }
      .switch {
        float: left;
      }
    </style>
  </head>

  <body>
    
    <div id="container">
      <h4 style="font-family: monospace;">416 Light Control</h4>
      <div class="card">
        <span class="text">Door side</span>
        <button class="mdl-button mdl-js-button mdl-button--fab" onclick="sw1Off()">
          <i class="material-icons" style="color: white;">power_settings_new</i>
        </button>
        <button class="mdl-button mdl-js-button mdl-button--fab" onclick="sw1On()">
          <i class="material-icons" style="color: white;">wb_incandescent</i>
        </button>
      </div>
      
      <div class="card">
        <span class="text">Windows side</span>
        <button class="mdl-button mdl-js-button mdl-button--fab" onclick="sw2Off()">
          <i class="material-icons" style="color: white;">power_settings_new</i>
        </button>
        <button class="mdl-button mdl-js-button mdl-button--fab" onclick="sw2On()">
          <i class="material-icons" style="color: white;">wb_incandescent</i>
        </button>
      </div>
    </div>
    
    <script src="https://code.jquery.com/jquery-1.12.1.min.js"></script>
    <script>
      function sw1On() {
        console.log("1on");
        $.post("/sw1", {led:"ON"});
      }
      function sw1Off() {
        console.log("1off");
        $.post("/sw1", {led:"OFF"});
      }
      function sw2On() {
        console.log("2on");
        $.post("/sw2", {led:"ON"});
      }
      function sw2Off() {
        console.log("2off");
        $.post("/sw2", {led:"OFF"});
      }
    </script>
  </body>
</html>
)=====";
