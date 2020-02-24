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
        <div class="switch">
          <label class="mdl-switch mdl-js-switch mdl-js-ripple-effect" for="switch-1">
            <input type="checkbox" id="switch-1" class="mdl-switch__input" onclick="sw1Clicked()">
            <span class="mdl-switch__label"></span>
          </label>
        </div>
        
      </div>
      
      <div class="card">
        <span class="text">Windows side</span>
        <div class="switch">
          <label class="mdl-switch mdl-js-switch mdl-js-ripple-effect" for="switch-2">
            <input type="checkbox" id="switch-2" class="mdl-switch__input" onclick="sw2Clicked()">
            <span class="mdl-switch__label"></span>
          </label>
        </div>
        
      </div>
    </div>
    
    <script src="https://code.jquery.com/jquery-1.12.1.min.js"></script>
    <script>
      function sw1Clicked() {
        var checkBox = document.getElementById("switch-1");
        if (checkBox.checked == true){
          console.log("on");
          $.post("/sw1", {led:"ON"});
        } else {
          console.log("off");
          $.post("/sw1", {led:"OFF"});
        }
      }
      
      function sw2Clicked() {
        var checkBox = document.getElementById("switch-2");
        if (checkBox.checked == true){
          console.log("on");
          $.post("/sw2", {led:"ON"});
        } else {
          console.log("off");
          $.post("/sw2", {led:"OFF"});
        }
      }

    </script>
  </body>
</html>
)=====";
