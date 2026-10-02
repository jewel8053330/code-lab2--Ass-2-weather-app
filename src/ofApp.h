#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		ofTrueTypeFont mainFont;
		ofTrueTypeFont titleFont;
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// Stores the location entered by the user
		string locationInput = "";
		string lastSearchedLocation = "";
		// Weather information returned by the API
		string cityName = "";
		string countryName = "";
		string weatherCondition = "";
		string lastUpdated = "";
		string errorMessage = "";

		float temperature = 0;
		float feelsLike = 0;
		float windSpeed = 0;
		int humidity = 0;

		bool weatherLoaded = false;
		// Map coordinates
		float latitude = 0;
		float longitude = 0;

		// Images
		ofImage worldMap;
		ofImage weatherIcon;
		ofImage cityPhoto;
		ofImage countryFlag;

		// Recent searches
		vector<string> recentSearches;

		// WeatherAPI key
		string apiKey = "7681e887e924434a828225913260909";

		// Function used to request weather data
		void getWeather();
		
};
