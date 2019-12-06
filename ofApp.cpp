#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	auto radius = 300;
	auto deg_span = 9;
	for (auto deg_start = 0; deg_start < 360; deg_start += deg_span + 1) {

		auto deg = deg_start;
		auto noise_value = ofNoise(radius * cos(deg_start * DEG_TO_RAD) * 0.002, radius * sin(deg_start * DEG_TO_RAD) * 0.002, ofGetFrameNum() * 0.008);
		auto max_height = ofMap(noise_value, 0.25, 0.75, 0, 1000);
		if (noise_value < 0.25) {

			max_height = 0;
		}
		else if (noise_value > 0.75) {

			max_height = 1000;
		}

		for (auto height = 0; height < max_height; height += 10) {

			int index = this->face.getNumVertices() - 2;

			this->face.addVertex(glm::vec3(radius * cos((deg) * DEG_TO_RAD), height, radius * sin((deg) * DEG_TO_RAD)));
			this->face.addVertex(glm::vec3(radius * cos((deg + deg_span) * DEG_TO_RAD), height, radius * sin((deg + deg_span) * DEG_TO_RAD)));

			this->frame.addVertex(glm::vec3(radius * cos(deg * DEG_TO_RAD), height, radius * sin(deg * DEG_TO_RAD)));
			this->frame.addVertex(glm::vec3(radius * cos((deg + deg_span) * DEG_TO_RAD), height, radius * sin((deg + deg_span) * DEG_TO_RAD)));

			if (height > 0) {

				this->face.addIndex(index); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				this->frame.addIndex(index); this->frame.addIndex(index + 2);
				this->frame.addIndex(index + 1); this->frame.addIndex(index + 3);
			}
			else if (height == 0) {

				this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 1);
			}

			deg += 5;
		}

		if (max_height > 0) {

			this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 1);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(0, -500, 0);

	ofSetColor(39);
	this->face.drawFaces();

	ofSetColor(139, 139, 239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}