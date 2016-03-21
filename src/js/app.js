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
var routes = [];
var names = [];
var times = [];

function getStopsCallback(responseText) {
	// Parse the received info
	var json = JSON.parse(responseText);
	console.log(responseText);
	var i;
	console.log(i);

	for (i = 0; i < stops.length; i++) {
		if (json.Code) {
			// If an error was returned, log it (I'll have to do something to display errors on the watch)
			console.log("Error " + json.Code);
			stopscounter.push(json.Code);
			routes[i] = "Error " + json.Code + "\u00BB";
			names[i] = "Error " + json.Code + "\u00BB";
			times[i] = "Error " + json.Code + "\u00BB";
		} else {
			// Else push the next arriving bus info to the arrays
			stopscounter.push(json[0].RouteNo);
			routes[i] = + json[0].RouteNo + "\u00BB";
			names[i] = json[0].Schedules[0].Destination + "\u00BB";
			times[i] = json[0].Schedules[0].ExpectedCountdown + "\u00BB";
		}
		
		break;
	}
	
	// Once we've fetched all the info, send it to the watch
	if (stopscounter.length == stops.length) {
		console.log("Sending data");
		console.log("Routes to send " + routes);
		console.log("Names to send " + names);
		console.log("Times to send " +times);
		//sendData();
	}
}

function getStops(i) {
	console.log("Getting stop " + i);
	var requrl;

	if (isNaN(stops[i])) {
		console.log("Stop " + i + " is NaN");
	} else {
		console.log("Stop " + i + " is " + stops[i]);
		requrl = "http://api.translink.ca/rttiapi/v1/stops/" + stops[i] + "/estimates?apikey=hCnIQTl1g1LNlWOZhEfa";
		console.log("Stop " + i + " URL is " + requrl);
		xhrRequest(requrl, "GET", function(responseText) {
				console.log("Sending request for stop " + i);
				var json = JSON.parse(responseText);
				console.log(responseText);
			
				if (json.Code) {
					// If an error was returned, log it (I'll have to do something to display errors on the watch)
					//console.log("Error " + json.Code);
					stopscounter.push(json.Code);
					routes[i] = "Error " + json.Code;
					names[i] = "Error " + json.Code;
					times[i] = "Error " + json.Code;
				} else {
					// Else push the next arriving bus info to the arrays
					stopscounter.push(json[0].RouteNo);
					console.log("Stop " + i + ", " + json[0].RouteNo + json[0].Schedules[0].Destination + json[0].Schedules[0].ExpectedCountdown);
					routes[i] = json[0].RouteNo;
					names[i] = json[0].Schedules[0].Destination;
					times[i] = json[0].Schedules[0].ExpectedCountdown;
				}
			
				// All done with the stops!
				if (stopscounter.length == stops.length) {
						console.log("=====Parsed all stops=====");
						sendData();
				}
			}
		);
	}
	
	
}

function sendData() {
	console.log("Routes to send: " + routes);
	console.log("Names to send: " + names);
	console.log("Times to send: " + times);
	
	/*console.log("Sending arrivals info");
    Pebble.sendAppMessage({
			stopRoutes: routes,
			stopDests: names,
			arrivalTimes: times
    }, function(e) {
      console.log('Send successful!');
			console.log(e);
    }, function(e) {
      console.log('Send failed!');
			console.log(e);
    });*/
	
	var number_of_stops = stops.length;
	var routes_dict = {};
	var names_dict = {};
	var times_dict = {};
	
	for (var i = 0; i < routes.length; i++ ) {
		routes_dict["routes" + i] = routes[i];
		routes_dict["names" + i] = names[i];
		routes_dict["times" + i] = times[i];
		console.log("Routes " + i + ": " + routes_dict["routes" + i]);
		console.log("Names " + i + ": " + routes_dict["names" + i]);
		console.log("Times " + i + ": " + routes_dict["times" + i]);
	}
	
	/*for (i = 0; i < names.length; i++ ) {
		names_dict["names" + i] = names[i];
		console.log("Names dictionary " + i + ": " + names_dict["names" + i]);
	}
	
	for (i = 0; i < times.length; i++ ) {
		times_dict["times" + i] = times[i];
		console.log("Times dictionary " + i + ": " + times_dict["times" + i]);
	}*/
	
	/*Pebble.sendAppMessage({
			numberOfStops: number_of_stops,
    }, function(e) {
      console.log('Send successful!');
			console.log(e);
    }, function(e) {
      console.log('Send failed!');
			console.log(e);
    });*/
	
	 Pebble.sendAppMessage(routes_dict,
        function(e) {
          console.log("Bus info sent to Pebble successfully!");
					console.log(e);
        },
        function(e) {
          console.log("Error sending bus info to Pebble!");
					console.log(e);
        }
   );
}

function wipeArrays() {
	inputs = [];
	stops = [];
	stopscounter = [];
	routes = [];
	names = [];
	times = [];
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
  var url = 'http://c055b373.ngrok.io';

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
			console.log("Stop " + i + " is " + inputs[i] + ", adding to stops");
			stops.push(inputs[i]);
		}
	}
	
	// Fetch info from TransLink
	for (i = 0; i < stops.length; i++) {
		console.log("getStops " + i);
		getStops(i);
	}
	
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