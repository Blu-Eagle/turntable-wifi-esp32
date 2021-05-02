String sliderValue = "255";


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <title>DIY Turntable</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">

    
    <style>
        html {font-family: Arial; display: inline-block; text-align: center;}
        h2 {font-size: 3.0rem;}
        p {font-size: 3.0rem;}
        body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
        .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
        .switch input {display: none}
        .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
        .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
        input:checked+.slider {background-color: #b30000}
        input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
    </style>

    <style>
        input[type=range] {
          -webkit-appearance: none;
          margin: 10px 0;
          width: 100%;
        }
        input[type=range]:focus {
          outline: none;
        }
        input[type=range]::-webkit-slider-runnable-track {
          width: 100%;
          height: 13px;
          cursor: pointer;
          animate: 0.2s;
          box-shadow: 2px 2px 5px #000000;
          background: #3071A9;
          border-radius: 6px;
          border: 1px solid #000000;
        }
        input[type=range]::-webkit-slider-thumb {
          box-shadow: 1px 1px 1px #000000;
          border: 1px solid #000000;
          height: 32px;
          width: 19px;
          border-radius: 8px;
          background: #FFFFFF;
          cursor: pointer;
          -webkit-appearance: none;
          margin-top: -10.5px;
        }
        input[type=range]:focus::-webkit-slider-runnable-track {
          background: #3071A9;
        }
        input[type=range]::-moz-range-track {
          width: 100%;
          height: 13px;
          cursor: pointer;
          animate: 0.2s;
          box-shadow: 2px 2px 5px #000000;
          background: #3071A9;
          border-radius: 6px;
          border: 1px solid #000000;
        }
        input[type=range]::-moz-range-thumb {
          box-shadow: 1px 1px 1px #000000;
          border: 1px solid #000000;
          height: 32px;
          width: 19px;
          border-radius: 8px;
          background: #FFFFFF;
          cursor: pointer;
        }
        input[type=range]::-ms-track {
          width: 100%;
          height: 13px;
          cursor: pointer;
          animate: 0.2s;
          background: transparent;
          border-color: transparent;
          color: transparent;
        }
        input[type=range]::-ms-fill-lower {
          background: #3071A9;
          border: 1px solid #000000;
          border-radius: 12px;
          box-shadow: 2px 2px 5px #000000;
        }
        input[type=range]::-ms-fill-upper {
          background: #3071A9;
          border: 1px solid #000000;
          border-radius: 12px;
          box-shadow: 2px 2px 5px #000000;
        }
        input[type=range]::-ms-thumb {
          box-shadow: 1px 1px 1px #000000;
          border: 1px solid #000000;
          height: 32px;
          width: 19px;
          border-radius: 8px;
          background: #FFFFFF;
          cursor: pointer;
        }
        input[type=range]:focus::-ms-fill-lower {
          background: #3071A9;
        }
        input[type=range]:focus::-ms-fill-upper {
          background: #3071A9;
        }
    </style>

    
  </head>
  
  <body>
    <h2>DIY Turntable</h2>

    <p><span id="textSliderValue">%SLIDERVALUE%</span></p>
    <p><input type="range" onchange="updateSliderPWM(this)" id="pwmSlider" min="0" max="255" value="%SLIDERVALUE%" step="1" class="istyle"></p><br><br>
    %PLACEHOLDER%
    
  </body>

  <script>
  function toggleCheckbox(element) {
    var xhr = new XMLHttpRequest();
    if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
    else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
    xhr.send();
  }

  function updateSliderPWM(element) {
    var sliderValue = document.getElementById("pwmSlider").value;
    document.getElementById("textSliderValue").innerHTML = sliderValue;
    console.log(sliderValue);
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/slider?value="+sliderValue, true);
    xhr.send();
  }
</script>
  
</html>
)rawliteral";



String processor(const String& var)
{
 
  if(var == "PLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Rotating Direction</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"1\" ><span class=\"slider\"></span></label>";
    return buttons;
  }
    if (var == "SLIDERVALUE"){
    return sliderValue;
  }
 
  return String();
}
