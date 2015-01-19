/* -----------------------------
  BARK TRACKER
  Justin Smith - justin@isamaker.com
  @justinIsAMaker

  Listen for sound over a certain threshold, report that sound to a feed on data.sparkfun.com
------------------------------ */

// Require MRAA and Request libraries
var m = require('mraa');
var request = require('request');

// Do a sanity check to make sure that MRAA is loaded
console.log('MRAA Version: ' + m.getVersion());

// Declare your sensor as an analog input
var soundSensor = new m.Aio(0);

// Set the sound threshold
var threshold = 700;

// Run the function to start out
checkSoundLevels();

// Declare the sound check function
function checkSoundLevels(){
  // read the value to start off
  var soundValue = soundSensor.read();

  // Log the value to see where you need to set the threshold - uncomment this line to debug
  //console.log(soundValue);

  // If the sound is higher than the threshold, make the request
  if(soundValue >= threshold){
    // Use the request library to hit the Sparkfun URL - make sure you replace the applicable parts with your data
		request('http://data.sparkfun.com/input/[YOUR STREAM ID]?private_key=[YOUR PRIVATE KEY]&decibel=' + soundValue, function(error, response, body){
      console.log(response.statusCode);
      // If the response is good, wait 5 seconds before we start checking again
      if(response.statusCode === 200){
      	console.log('posted successfully');
      	setTimeout(function(){}, 5000);
      	setTimeout(checkSoundLevels, 100);
      } else {
      	console.log('oops, there was an error');
      	setTimeout(checkSoundLevels, 100);
      }
		});
  } else {
  	setTimeout(checkSoundLevels, 100);
  }
}