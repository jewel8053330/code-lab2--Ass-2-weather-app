#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Set the application window title
	ofSetWindowTitle("World Weather App");

	// Set the background colour
	ofSetBackgroundColor(25, 45, 75);

	mainFont.load("verdana.ttf", 18);
	titleFont.load("verdana.ttf", 28);

	if (worldMap.load("worldmap.png")) {
		ofLogNotice() << "WORLD MAP LOADED SUCCESSFULLY";
	} else {
		ofLogError() << "WORLD MAP FAILED TO LOAD";
	}
}
//--------------------------------------------------------------
void ofApp::update() {

}

	//--------------------------------------------------------------
	void ofApp::getWeather() {
	weatherLoaded = false;
	errorMessage = "";

		if (locationInput.empty()) {
			errorMessage = "Please enter a location.";
			weatherLoaded = false;
			return;
		}
		lastSearchedLocation = locationInput;
		string url = "https://api.weatherapi.com/v1/current.json?key=" + apiKey + "&q=" + locationInput;

		ofHttpResponse response = ofLoadURL(url);

		if (response.status == 200) {

			try {
				ofJson jsonData = ofJson::parse(response.data.getText());

				cityName = jsonData["location"]["name"];
				countryName = jsonData["location"]["country"];

				latitude = jsonData["location"]["lat"];
				longitude = jsonData["location"]["lon"];

				temperature = jsonData["current"]["temp_c"];
				feelsLike = jsonData["current"]["feelslike_c"];
				humidity = jsonData["current"]["humidity"];
				windSpeed = jsonData["current"]["wind_kph"];

				weatherCondition = jsonData["current"]["condition"]["text"];
				lastUpdated = jsonData["current"]["last_updated"];

				weatherLoaded = true;
				errorMessage = "";
			} catch (...) {
				errorMessage = "Could not read weather data.";
				weatherLoaded = false;
			}
		} else {
			errorMessage = "Location not found or API error.";
			weatherLoaded = false;
		}
	}

	
//--------------------------------------------------------------
void ofApp::draw() {

	// Main heading
	ofSetColor(255);
	titleFont.drawString("WORLD WEATHER APP", 300, 100);

	// Instructions
	mainFont.drawString("Enter a location to check the current weather", 230, 150);
	// Search box
	ofSetColor(255);
	ofDrawRectangle(230, 200, 350, 50);
	// Display the location typed by the user
	ofSetColor(30);
	mainFont.drawString(locationInput, 245, 235);

	// Search button hover effect
	if (mouseX >= 600 && mouseX <= 720 && mouseY >= 200 && mouseY <= 250) {

		ofSetColor(90, 170, 250);
	} else {
		ofSetColor(70, 150, 230);
	}

	ofDrawRectangle(600, 200, 120, 50);

	ofSetColor(255);
	
	mainFont.drawString("SEARCH", 610, 235);

	// Clear button hover effect
	if (mouseX >= 735 && mouseX <= 835 && mouseY >= 200 && mouseY <= 250) {

		ofSetColor(150, 150, 150);
	} else {
		ofSetColor(120, 120, 120);
	}

	ofDrawRectangle(735, 200, 100, 50);

	ofSetColor(255);
	mainFont.drawString("CLEAR", 745, 235);

	// Display world map
	ofSetColor(255);
	worldMap.draw(270, 600, 500, 250);
	// Show searched location on the map
	if (weatherLoaded) {
		float markerX = ofMap(longitude, -180, 180, 270, 770);
		float markerY = ofMap(latitude, 90, -90, 600, 850);

		ofSetColor(0, 255, 255);
		ofDrawCircle(markerX, markerY, 8);
	}
	// Display weather information
	if (weatherLoaded && locationInput == lastSearchedLocation) {
		// Weather information panel
		ofSetColor(35, 60, 95);
		ofDrawRectangle(220, 280, 600, 270);

		ofSetColor(255);
		mainFont.drawString(
			"Location: " + cityName + ", " + countryName,
			230, 310);

		mainFont.drawString(
			"Temperature: " + ofToString(temperature) + " C",
			230, 345);

		mainFont.drawString(
			"Feels like: " + ofToString(feelsLike) + " C",
			230, 380);

		mainFont.drawString(
			"Humidity: " + ofToString(humidity) + "%",
			230, 415);

		mainFont.drawString(
			"Wind speed: " + ofToString(windSpeed) + " km/h",
			230, 450);

		mainFont.drawString(
			"Condition: " + weatherCondition,
			230, 485);

		mainFont.drawString(
			"Last updated: " + lastUpdated,
			230, 520);
	}
	// Display an error if something went wrong
	if (!errorMessage.empty()) {
		ofSetColor(255, 100, 100);
		mainFont.drawString(errorMessage, 230, 300);
	}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// Backspace removes the last character
	if (key == OF_KEY_BACKSPACE) {
		if (!locationInput.empty()) {
			locationInput.pop_back();
		}

		weatherLoaded = false;
		errorMessage = "";
	}

	// Press Enter to search
	else if (key == OF_KEY_RETURN) {
		getWeather();
	}

	// Add normal keyboard characters
	else if (key >= 32 && key <= 126) {
		locationInput += (char)key;

		weatherLoaded = false;
		errorMessage = "";
	}
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

		// Search button
		if (x >= 600 && x <= 720 && y >= 200 && y <= 250) {

			getWeather();
		}

		// Clear button
		if (x >= 735 && x <= 835 && y >= 200 && y <= 250) {

			locationInput = "";
			weatherLoaded = false;
			errorMessage = "";
		}
	}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
