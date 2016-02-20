var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.setRequestHeader("Accept", "application/JSON");
  xhr.send();
};

var stops = [];

function getStops() {
	function getStopsCallback(responseText) {
			var json = JSON.parse(responseText);
			console.log(responseText);
		
			if (json.Code) {
				console.log("Error " + json.Code);
			} else {
				console.log(json[0].RouteNo);
			}
	}
	
	for (var i = 0; i < stops.length; i++) {
		console.log("Parsing stop " + i);
		var requrl;
		
		if (isNaN(stops[i])) {
			console.log("NaN");
		} else {
			console.log(stops[i]);
			requrl = "http://api.translink.ca/rttiapi/v1/stops/" + stops[i] + "/estimates?apikey=hCnIQTl1g1LNlWOZhEfa";
			console.log(requrl);
			xhrRequest(requrl, "GET", getStopsCallback);
		}
	}
}

Pebble.addEventListener('ready', function() {
	console.log('PebbleKit JS Ready!');
});

Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
    console.log('Message contents: ' + JSON.stringify(e.payload));
		
		getStops();
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
	// Add stops to array
	stops.push(parseInt(configData.stopOne), parseInt(configData.stopTwo), parseInt(configData.stopThree), parseInt(configData.stopFour), parseInt(configData.stopFive));
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