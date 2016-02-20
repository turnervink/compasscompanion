var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.setRequestHeader("Accept", "application/JSON");
  xhr.send();
};

var inputs = [];
var stops = [];
var stopscounter = [];
var routes;
var names;
var times;

function getStopsCallback(responseText) {
	// Parse the received info
	var json = JSON.parse(responseText);
	console.log(responseText);

	if (json.Code) {
		// If an error was returned, log it (I'll have to do something to display errors on the watch)
		console.log("Error " + json.Code);
		stopscounter.push(json.Code);
		routes += "Error " + json.Code + "\u00BB";
		names += "Error " + json.Code + "\u00BB";
		times += "Error " + json.Code + "\u00BB";
	} else {
		// Else push the next arriving bus info to the arrays
		stopscounter.push(json[0].RouteNo);
		routes += json[0].RouteNo + "\u00BB";
		names += json[0].Schedules[0].Destination + "\u00BB";
		times += json[0].Schedules[0].ExpectedCountdown + "\u00BB";
	}
	
	// Once we've fetched all the info, send it to the watch
	if (stopscounter.length == stops.length) {
		console.log("Sending data");
		sendData();
	}
}

function getStops() {
	// Parse each inputted stop and send an HTTP request
	for (var i = 0; i < stops.length; i++) {
		console.log("Parsing stop " + i);
		var requrl;
		
		if (isNaN(stops[i])) {
			console.log("Stop " + i + " is NaN");
		} else {
			console.log("Stop " + i + " is " + stops[i]);
			requrl = "http://api.translink.ca/rttiapi/v1/stops/" + stops[i] + "/estimates?apikey=hCnIQTl1g1LNlWOZhEfa";
			console.log("Stop " + i + " URL is " + requrl);
			xhrRequest(requrl, "GET", getStopsCallback);
		}
	}
	
	// All done with the stops!
	console.log("=====Parsed all stops=====");
}

function sendData() {
	console.log("Routes to send: " + routes);
	console.log("Names to send: " + names);
	console.log("Times to send: " + times);
	
	console.log("Sending config settings");
    Pebble.sendAppMessage({
			stopRoutes: routes + "\0",
			stopDests: names,
			arrivalTimes: times
    }, function(e) {
      console.log('Send successful!');
			console.log(e);
    }, function(e) {
      console.log('Send failed!');
			console.log(e);
    });
}

function wipeArrays() {
	inputs = [];
	stops = [];
	stopscounter = [];
	routes = "";
	names = "";
	times = "";
}

Pebble.addEventListener('ready', function() {
	console.log('PebbleKit JS Ready!');
});

Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
  }
);

//===== Config =====//

Pebble.addEventListener('showConfiguration', function() {
  var url = 'http://970ce33.ngrok.com';

  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));

  console.log('Configuration page returned: ' + JSON.stringify(configData));
	
	// Clear arrays
	wipeArrays();
	
	// Grab all user inputted stops
	inputs.push(parseInt(configData.stopOne), parseInt(configData.stopTwo), parseInt(configData.stopThree), parseInt(configData.stopFour), parseInt(configData.stopFive));
	
	// Discard any empty stop inputs
	for (var i = 0; i < inputs.length; i++) {
		if (isNaN(inputs[i])) {
			console.log("Stop " + i + " is NaN, not adding to stops");
		} else {
			stops.push(inputs[i]);
		}
	}
	
	// Fetch info from TransLink
	getStops();
	
  /*if (configData.stopOne >= 0) { // If we have received the correct data (not sure why we wouldn't, but who knows?)
		// Send all keys to Pebble
		console.log("Sending config settings");
    Pebble.sendAppMessage({
			stopOne: parseInt(configData.stopOne),
			stopTwo: parseInt(configData.stopTwo),
			stopThree: parseInt(configData.stopThree),
			stopFour: parseInt(configData.stopFour),
			stopFive: parseInt(configData.stopFive),
    }, function(e) {
      console.log('Send successful!');
			console.log(e);
    }, function(e) {
      console.log('Send failed!');
			console.log(e);
    });
  }*/
});