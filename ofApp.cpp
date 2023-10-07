#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(0);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(140, 7);

	for (int x = -160; x <= 160; x += 320) {

		for (int y = -160; y <= 160; y += 320) {

			int start_index = this->mesh.getNumVertices();
			for (int i = 0; i < ico_sphere.getMeshPtr()->getNumVertices(); i++) {

				this->mesh.addVertex(ico_sphere.getMeshPtr()->getVertex(i) + glm::vec3(x, y, 0));
				this->mesh.addColor(ofColor(0));
			}

			for (int i = 0; i < ico_sphere.getMeshPtr()->getNumIndices(); i++) {

				this->mesh.addIndex(start_index + ico_sphere.getMeshPtr()->getIndex(i));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clearColors();
	auto noise_param = 0.00065;

	ofColor color;
	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		auto noise_value = ofMap(ofNoise(
			this->mesh.getVertex(i).x * noise_param,
			this->mesh.getVertex(i).y * noise_param,
			ofGetFrameNum() * 0.005), 0, 1, 0, 20);

		color.setHsb(ofMap(noise_value > 10 ? noise_value - 10 : noise_value, 0, 10, 0, 255), 150, 255);
		int int_noise_value = (int)noise_value;
		noise_value = noise_value - int_noise_value;
		auto alpha = abs(noise_value - 0.5) < 0.35 ? 0 : ofMap(abs(noise_value - 0.5), 0.35, 0.5, 0, 255);
		
		color = ofColor(color, alpha);
		this->mesh.addColor(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int x = -160; x <= 160; x += 320) {

		for (int y = -160; y <= 160; y += 320) {

			ofDrawSphere(glm::vec3(x, y, 0), 139);
		}
	}

	this->mesh.drawFaces();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}