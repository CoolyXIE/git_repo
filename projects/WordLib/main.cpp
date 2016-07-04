#include <iostream>
#include "curl/curl.h"

using namespace std;


FILE *fp;

size_t voice_writer(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int written = fwrite(ptr, size, nmemb, (FILE *)fp);
    return written;
}

void query_and_save_voice(string word){
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    string voice_url = "http://dict.youdao.com/dictvoice?audio=";
    voice_url += word + "&type=2";
    curl_easy_setopt(curl, CURLOPT_URL, voice_url.c_str());
    string fileName = "C:\\Users\\Administrator\\Desktop\\" + word + ".avi";
    if((fp = fopen(fileName.c_str(), "w")) == NULL){
        curl_easy_cleanup(curl);
        exit(1);
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, voice_writer);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

}


int main()
{
    query_and_save_voice("happybirthday");
    return 0;
}
