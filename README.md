#study__ofxHapPlayer

##環境
*	Xcode : 7.2
*	oF : 0.9.0

##add on
ofxHapPlayer  
release OF 0.9  
https://github.com/bangnoise/ofxHapPlayer  

Hap codec download  
https://github.com/vidvox/hap-qt-codec/releases/  
v9

##Contents
ofxHapPlayerのtest.

*	自前shaderにpassして描画 : OK
*	6 file : 1920 x 1080 : 60FPS : OK


##note
*	ofxHapPayerは、Xcodeにて、32bit modeにしないとBuild Errorとなる。
	https://github.com/bangnoise/ofxHapPlayer/issues/15
	
	32bit modeは、  
	Build Settings -> Architectures -> Architectures  
	から。


*	複数fileを切り替えながら使用したい場合。  
	都度、対象をplay()で起動しても十分速かったが、先頭にblock noiseが乗る。  
	そこで、ofApp::setup()でplay()までしておき、ofApp::update()及び、ofApp::draw()
	では、対象objectのみ、update(), draw()すればOK。
	これで、十分速く、ノイズもなく再生可能であった。
	

*	codecをinstallすると、どこに保存されるのか。  

	http://bison.jp/macosx/872.html  
	現段階での動画再生用 無料 Codecまとめ的なものは以下の四つです。
	それぞれ、Libraryフォルダ下QuickTimeフォルダ( /Library/QuickTime or  ~/Library/QuickTime ) に QuickTimeコンポーネントを入れたり、
	Applications フォルダ ( /Applications )にアプリを入れたり、Internetプラグインフォルダ (/Library/Internet Plug-Ins )をプラグインを入れたりします。
	
