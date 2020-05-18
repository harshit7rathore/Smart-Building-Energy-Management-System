//var canvas;
var score;
var button;
//var initialInput;
//var submitButton;
var database;

function setup() {


  var config = {
    apiKey: "AIzaSyA3izxVIG3sMvIslDZYKl_z7wVj4W0DYxM",
    authDomain: "smart-india-hackathon-harshit.firebaseapp.com",
    databaseURL: "https://smart-india-hackathon-harshit.firebaseio.com",
    projectId: "smart-india-hackathon-harshit",
    storageBucket: "smart-india-hackathon-harshit.appspot.com",
    messagingSenderId: "810102811212",
    appId: "1:810102811212:web:3a155b42efc448a754a2e9",
    measurementId: "G-XHHFXCZ1WM"
  };
  firebase.initializeApp(config);
  database = firebase.database();

  var ref = database.ref('/');
  ref.on('value', gotData, errData);






}

function gotData(data) {

  var temp = data.val().Temp;
  var light = data.val().LDR;
  var humidity = data.val().Humidity;
  var airq = data.val().Air_Quality;


  document.getElementById("temp").innerHTML = temp;
  document.getElementById("light").innerHTML = light;
  document.getElementById("humidity").innerHTML = humidity;
  document.getElementById("airq").innerHTML = airq;

}

function errData(err) {
  console.log('Error!');
  console.log(err);
}









function draw() {
  background(0);
  textAlign(CENTER);
  textSize(32);
  fill(255);
  text(score, width / 2, height / 2);
}