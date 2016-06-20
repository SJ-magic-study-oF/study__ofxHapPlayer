/************************************************************
ffmpegを使って、HAP codecのvideoに変換する

	ffmpegにhap encode機能を追加するため、snappyを追加する
		Homebrewでインストールしたffmpegに機能を追加する方法
			http://www.nishimiyahara.net/2015/01/20/145837
				再インストール
					brew update
					brew reinstall --with-opus
				
				どのencoderが使えるか
					brew info ffmpeg
		
		brew reinstall ffmpeg --with-snappy
	
	対応済みcodec/ format の確認方法
		ffmpeg -codecs
		ffmpeg -formats
	
	do convert
		HAP
			ffmpeg -i test.mp4 -vcodec hap -format hap_q out.mov
		HAP Q
			ffmpeg -i test.mp4 -vcodec hap -format hap   out.mov 
	
	HAP codec variation
		Hap			- Reasonable image quality
		Hap Alpha	- Reasonable image quality with an alpha channel
		Hap Q		- Good image quality at a higher data-rate
		Hap Q Alpha	- Good image quality with an alpha channel at a higher data-rate
************************************************************/



#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxHapPlayer.h"


/************************************************************
define
************************************************************/
#define TYPE__SINGLE_FILE		0
#define TYPE__FILESET			1
#define TYPE__SHADER			2
	#define EXE_TYPE TYPE__SHADER


/************************************************************
class
************************************************************/

/**************************************************
**************************************************/
class HAP_VIDEO_SET{
private:
	enum{
		NUM_VIDEOS = 3,
	};
	
	int id;
	int offset;
	ofxHapPlayer video[NUM_VIDEOS];
	
	bool b_Ready;
	
public:
	HAP_VIDEO_SET()
	: b_Ready(false), id(0), offset(0)
	{
	}
	
	void setup(int _offset)
	{
		offset = _offset;
		
		for(int i = 0; i < NUM_VIDEOS; i++){
			char buf[500];
			sprintf(buf, "%d.mov", i + offset);
			
			video[i].load( buf );	//Load the video file
			
			video[i].setLoopState(OF_LOOP_NORMAL);
			video[i].setSpeed(1);
			
			video[i].setVolume(0);
			video[i].play();
		}
		
		b_Ready = true;
	}
	
	void update()
	{
		if(!b_Ready) return;
		
		for(int i = 0; i < NUM_VIDEOS; i++){
			video[i].update();
		}
	}
	
	void SetId(int _id)
	{
		if(0 <= id && id < NUM_VIDEOS){
			id = _id;
		}
	}
	
	void draw()
	{
		if(!b_Ready) return;
		
		video[id].draw(0, 0, ofGetWidth(), ofGetHeight());
	}
};

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
	private:
		enum{
			NUM_VIDEO_SETS = 2,
			NUM_VIDEO_ARRAY = 6,
		};
		
		HAP_VIDEO_SET HapVideo_set[NUM_VIDEO_SETS];
		int id_VideoSet;
		bool b_shift;
		
		ofxHapPlayer player;
		ofxHapPlayer playerArray[NUM_VIDEO_ARRAY];
		
		ofShader shader;	//Shader
		ofFbo fbo;			//First buffer for input image
		ofFbo fbo2;			//Second buffer for mask
		
		bool b_Ready;
		

	public:
		ofApp();
		
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
};
