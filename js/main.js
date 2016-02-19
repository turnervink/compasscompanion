(function () {

	loadOptions();
	submitHandler();
})();

function validateLengths() {
  var stopOne = document.getElementById("stopOne");
  var stopTwo = document.getElementById("stopTwo");
  var stopThree = document.getElementById("stopThree");
  var stopFour = document.getElementById("stopFour");
  var stopFive = document.getElementById("stopFive");

  var rightLength = true;

  if (stopOne.value > 99999 || stopOne.value.length < 5 && stopOne.value != 0) {
    stopOne.style.color = "red";
    rightLength = false;
  } else {
    stopOne.style.color = "black";
  }

  if (stopTwo.value > 99999 || stopTwo.value.length < 5 && stopTwo.value != 0) {
    stopTwo.style.color = "red";
    rightLength = false;
  } else {
    stopTwo.style.color = "black";
  }

  if (stopThree.value > 99999 || stopThree.value.length < 5 && stopThree.value != 0) {
    stopThree.style.color = "red";
    rightLength = false;
  } else {
    stopThree.style.color = "black";
  }

  if (stopFour.value > 99999 || stopFour.value.length < 5 && stopFour.value != 0) {
    stopFour.style.color = "red";
    rightLength = false;
  } else {
    stopFour.style.color = "black";
  }

  if (stopFive.value > 99999 || stopFive.value.length < 5 && stopFive.value != 0) {
    stopFive.style.color = "red";
    rightLength = false;
  } else {
    stopFive.style.color = "black";
  }
  console.log(rightLength);
  return rightLength;
}

function submitHandler() {
	var $submitButton = $('#submitButton');

	$submitButton.on('click', function() {
    if (validateLengths()) {
      console.log('Submit');
      $("#desc").text("Enter up to 5 stop IDs below.");
		  var return_to = getQueryParam('return_to', 'pebblejs://close#');
		  document.location = return_to + encodeURIComponent(JSON.stringify(getAndStoreConfigData()));
    } else {
      console.log("Length error");
      $("#desc").text("Make sure all IDs are 5 digits!");
    }
	});
}

function loadOptions() {
  var $stopOne = $("#stopOne");
  var $stopTwo = $("#stopTwo");
  var $stopThree = $("#stopThree");
  var $stopFour = $("#stopFour");
  var $stopFive = $("#stopFive");

  if (localStorage.stopOne) {
    $stopOne[0].value = localStorage.stopOne;
    $stopTwo[0].value = localStorage.stopTwo;
    $stopThree[0].value = localStorage.stopThree;
    $stopFour[0].value = localStorage.stopFour;
    $stopFive[0].value = localStorage.stopFive;
  }
}

function getAndStoreConfigData() {
  var $stopOne = $("#stopOne");
  var $stopTwo = $("#stopTwo");
  var $stopThree = $("#stopThree");
  var $stopFour = $("#stopFour");
  var $stopFive = $("#stopFive");

  var options = {
    stopOne: $stopOne.val(),
    stopTwo: $stopTwo.val(),
    stopThree: $stopThree.val(),
    stopFour: $stopFour.val(),
    stopFive: $stopFive.val()
  };

  localStorage.stopOne = options.stopOne;
  localStorage.stopTwo = options.stopTwo;
  localStorage.stopThree = options.stopThree;
  localStorage.stopFour = options.stopFour;
  localStorage.stopFive = options.stopFive;

  console.log('Got options: ' + JSON.stringify(options));
	return options;
}

function getQueryParam(variable, defaultValue) {
  var query = location.search.substring(1);
  var vars = query.split('&');
  for (var i = 0; i < vars.length; i++) {
    var pair = vars[i].split('=');
    if (pair[0] === variable) {
      return decodeURIComponent(pair[1]);
    }
  }
  return defaultValue || false;
}
