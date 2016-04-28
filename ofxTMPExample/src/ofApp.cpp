#include "ofMain.h"
#include "ofxTMP.h"

class ofApp : public ofBaseApp {
    template <typename R>
    R eval(std::function<R()> f) {
        return f();
    }
    
    template <typename F>
    typename ofxTMP::function_traits<F>::result_type eval(F f) {
        return eval(ofxTMP::cast_lambda(f));
    }
    
    template <typename T>
    typename ofxTMP::type_traits<T>::inner_type calc_sum(const T &v) {
        typename ofxTMP::type_traits<T>::inner_type sum{};
        for(std::size_t i = 0; i < ofxTMP::type_traits<T>::size; i++) {
            sum += v[i];
        }
        return sum;
    }
    
public:
    void setup() {
        ofLogNotice() << "version macro";
        
        ofLogNotice("current of version") << OFX_OF_VERSION;
        ofLogNotice("version 0.9.3") << OFX_MAKE_OF_VERSION(0, 9, 3);
#if OFX_THIS_OF_IS_OLDER_THAN(0, 9, 3)
        ofLogNotice("version check") << "this of lib is older than 0.9.3";
#else
        ofLogNotice("version check") << "this of lib is after 0.9.3";
#endif
        
        std::cout << std::endl;
        
        ofLogNotice() << "utilities";
        if(ofxTMP::is_cpp14()) {
            ofLogNotice("c++ version") << "c++14 is cool!";
        } else if(ofxTMP::is_cpp11()) {
            ofLogNotice("c++ version") << "c++11 is better.";
        } else {
            ofLogError("c++ version") << "what's happen!?";
        }
        
        std::cout << std::endl;
        
        ofLogNotice() << "type traits";
        ofVec2f v2 = {1.0f, 2.0f};
        ofVec3f v3 = {1.0f, 2.0f, 3.0f};
        ofVec4f v4 = {1.0f, 2.0f, 3.0f, 4.0f};
        ofFloatColor fc = {0.0f, 1.0f, 0.5f, 0.8f};
        ofColor c = {64, 64, 64, 64};
        
        ofLogNotice("ofVec2f") << calc_sum(v2);
        ofLogNotice("ofVec3f") << calc_sum(v3);
        ofLogNotice("ofVec4f") << calc_sum(v4);
        ofLogNotice("ofFloatColor") << calc_sum(fc);
        ofLogNotice("overflow") << (int)calc_sum(c);
        
        std::cout << std::endl;
        
        ofLogNotice() << "function traits";
        ofLogNotice("call directly") << eval(ofxTMP::cast_lambda([](){ return 8; }));
        ofLogNotice("wrap the method") << eval([](){ return 8; });
        
        ofExit();
    }
};

int main() {
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new ofApp);
}
