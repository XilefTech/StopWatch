$(document).ready(function () {
	$("#reset").click(function () {
		$.get("http://192.168.4.1:8080/reset", function (data) {
			console.log(data);
		})
	});

	$("#start").click(function () {
		$.get("http://192.168.4.1:8080/start", function (data) {
			console.log(data);
		})
	});
	
	$("#stop").click(function () {
		$.get("http://192.168.4.1:8080/stop", function (data) {
			console.log(data);
		})
	});

	$("#battery-refresh").click(function () {
		refreshBatteryStatus();
	});
});

setInterval(function ( ) {
	refreshBatteryStatus();
}, 10000);

function refreshBatteryStatus() {
	fetch('https://192.168.4.1:8080/battery-status', {
		method: 'GET',
		headers: {
			'Accept': 'application/json',
		},
	}).then(response => response.json())
	.then(data => {
		$("#battery-status").empty();
		data.forEach(function(battery) {
			$("#battery-status")
			.append("<div class='battery-status-item'>" + battery.nickName + " (" + battery.macAddress + "): " + battery.batteryLevel + "</div>");
		})
	})
}