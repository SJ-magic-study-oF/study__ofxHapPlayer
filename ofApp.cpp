#include "ofApp.h"

ofApp::ofApp()
: b_Ready(false)
{
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetWindowShape(1920, 1080);
	ofBackground(0, 0, 0);
	

#if (EXE_TYPE == TYPE__SINGLE_FILE)
	player.load("0.mov");
	player.play();

#elif (EXE_TYPE == TYPE__FILESET)	
	HapVideo_set[0].setup(0);
	HapVideo_set[1].setup(3);
	
	id_VideoSet = 0;
	b_shift = false;
	
#elif (EXE_TYPE == TYPE__SHADER)
	shader.load( "shaderVert.c", "shaderFrag.c" );

	fbo.allocate( ofGetWidth(), ofGetHeight() );
	fbo2.allocate( ofGetWidth(), ofGetHeight() );
	
	for(int i = 0; i < NUM_VIDEO_ARRAY; i++){
		char buf[500];
		sprintf(buf, "%d.mov", i);
		
		playerArray[i].load(buf);
		
		playerArray[i].setLoopState(OF_LOOP_NORMAL);
		playerArray[i].setSpeed(1.0);
		
		playerArray[i].setVolume(0);
		playerArray[i].play();
	}
#endif
	
	/********************
	player.isLoaded()
	で準備完了を判別すると、完了しきっておらず、先頭にブロックノイズが乗ることがあった。
	そこで、b_Readyをsetup()完了の判別に使用する。
	-> 効果まで確認済み.s
	********************/
	b_Ready = true;
}

//--------------------------------------------------------------
void ofApp::update(){
#if (EXE_TYPE == TYPE__SINGLE_FILE)
	if (player.isLoaded()){
		player.update();
	}
	
#elif (EXE_TYPE == TYPE__FILESET)
	HapVideo_set[id_VideoSet].update();
	
#elif (EXE_TYPE == TYPE__SHADER)
	if(b_Ready){
		/********************
		複数fileを同時に走らせてもFPSが落ちないことをcheck.
		********************/
		for(int i = 0; i < NUM_VIDEO_ARRAY; i++){
			playerArray[i].update();
		}
	}

#endif
}

//--------------------------------------------------------------
void ofApp::draw(){
#if (EXE_TYPE == TYPE__SINGLE_FILE)
	if (player.isLoaded()) // it is better to use "b_Ready" to avoid block noise on top frame.
	{
		ofSetColor(255, 255, 255);
		player.draw(0, 0);
	}
	
	// Draw the FPS display
	/*
	ofSetColor(20,20,20);
	ofDrawBitmapString(ofToString(ofGetFrameRate(), 0) + " FPS", 20, 20);
	*/
	
#elif (EXE_TYPE == TYPE__FILESET)
	ofSetColor(255, 255, 255);
	HapVideo_set[id_VideoSet].draw();

#elif (EXE_TYPE == TYPE__SHADER)
	if ( b_Ready ){
		/********************
		********************/
		fbo.begin();
		ofBackground( 0, 0, 0 );
		ofSetColor( 255, 255, 255 );
		
		playerArray[0].draw(0, 0);
		
		fbo.end();
	
		/********************
		********************/
		fbo2.begin();	
		ofBackground( 0, 0, 0 );
		ofSetColor( 255, 255, 255 );
		
		playerArray[1].draw(0, 0);
		
		fbo2.end();
	
		/********************
		********************/
		//NOTE: It is important to enable alpha blending for correct shader's working,
		//because shader performs masking by setting alpha-value of output color
		ofEnableAlphaBlending();		
	
		shader.begin();		
	
		// Last parameter 1 is OpenGL texture identifier
		// note that id = zero id used for default binding to texture0.
		shader.setUniformTexture( "texture1", fbo2.getTextureReference(), 1 ); 
	
		//Draw fbo image
		ofSetColor( 255, 255, 255 );
		fbo.draw( 0, 0 );
	
		shader.end();
		
		/********************
		********************/
		printf("%5.0f\r", ofGetFrameRate());
		fflush(stdout);
	}

#endif
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{	
#if (EXE_TYPE == TYPE__FILESET)
			int temp = key - '0';
			
			if(b_shift){
				if(temp < NUM_VIDEO_SETS){
					id_VideoSet = temp;
				}
			}else{
				HapVideo_set[id_VideoSet].SetId(temp);
			}
#endif
		}			
			break;
			
		case 'f':
		{
			static bool b_FullScreen = false;
			
			b_FullScreen = !b_FullScreen;
			
			ofSetFullscreen(b_FullScreen);
		}
			break;
		
		case OF_KEY_SHIFT:
			if(b_shift)	b_shift = false;
			else		b_shift = true;
			
			printf("b_shift = %d\n", b_shift);
			
			break;
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
void ofApp::mousePressed(int x, int y, int button){

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
