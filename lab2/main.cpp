#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <unistd.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include <map>
#include <time.h>
#include <thread>

using namespace std;

using json = nlohmann::json;

const int valute_ = 34;

struct obj{
    string name;
    double sum;
    vector<double> midiana;
};

char a = '0';

void wait(char &a){
    a = getchar();
}



//static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
//{
//    ((string*)userp)->append((char*)contents, size * nmemb);
//    return size * nmemb;
//}

//size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
//{
//    size_t new_len = s->len + size*nmemb;
//    s->ptr = realloc(s->ptr, new_len+1);
//    if (s->ptr == NULL) {
//        fprintf(stderr, "realloc() failed\n");
//        exit(EXIT_FAILURE);
//    }
//    memcpy(s->ptr+s->len, ptr, size*nmemb);
//    s->ptr[new_len] = '\0';
//    s->len = new_len;
//
//    return size*nmemb;
//}

static size_t Writer(char *buffer, size_t size, size_t nmemb, std::string *html) {
    int result = 0;
    if (buffer != nullptr) {
        html -> append(buffer, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

int main(){
    thread t(wait, ref(a));

    setlocale(LC_ALL, "Russian");
    std::string url = "https://www.cbr-xml-daily.ru/daily_json.js";
    json j;
    CURL *curl = curl_easy_init();
    CURLcode result;
    string readBuffer;
    vector<obj> middle;
    vector<double> arr[valute_];



    int i = 0;
    while(a == '0') {
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");
//      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            result = curl_easy_perform(curl);
            j = nlohmann::json::parse(readBuffer);
        }
//        cout << readBuffer;

        int counter = 0;
        for (json::iterator it = j["Valute"].begin(); it != j["Valute"].end(); ++it) {
            double a = it.value()["Value"];
            double b = it.value()["Nominal"];
            cout << it.key() << " : " << a / b << endl;

            if (i == 0) {
                    obj *temp = new obj;
                    temp->name = it.key();
                    temp->sum = a / b;
                    temp->midiana.push_back(a/b);
                    middle.push_back(*temp);
                    counter++;
            }
            else{
                    middle[counter].sum += a / b;
                    middle[counter].midiana.push_back(a/b);
                    counter++;
            }
        }
//        curl_easy_cleanup(curl);
        readBuffer.clear();

        cout << endl<< "-------------------------------------------------------------------------------------" << endl;
        sleep(10);
        i++;
    }
    cout << "MIDDLE:" << "          " <<"MIDIANA:"<< endl;
    for (int j = 0; j < middle.size(); ++j) {
        cout << middle[j].name << " : " << middle[j].sum/i;
        sort (middle[j].midiana.begin(), middle[j].midiana.end());
        cout << "  ||  "<<middle[j].midiana[i/2] << endl;
    }

//    int midl = i/2;

//    for (int i = 0; i < j["Valute"].size(); ++i) {
//        obj *temp = new obj;
//        temp->name = j["Valute"][i];
//        double a = j["Valute"][i]["Value"];
//        double b = j["Valute"][i]["Nominal"];
//        temp->sum = a / b;
//    }

    //std::string exemple = "{\"test\":1,\"cur\":{\"usd\":0.3,\"eur\":0.4}}";
    //json test;
    //test = json::parse(exemple);

//    for (json::iterator it = j["NumCode"].begin(); it != j["NumCode"].end(); ++it) {
//        std::cout << it.key() << " : " << it.value() << "\n";
//    }
    t.detach();
    return 0;
}
