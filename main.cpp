#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

template<class T>
std::vector<T> generate_random_vector(std::size_t num, T min = -10, T max = 10)
{
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(min, max);

    auto lambda = [&e2, &dist] () -> T { return dist(e2); };

    std::vector<T> result(num);
    std::generate_n(result.begin(), num, lambda);
    return result;
}


void first_func(){
    auto nums = generate_random_vector<float>(10,1.f,100.f);

    for(const auto num : nums){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    for(auto& num : nums) num *= 2.f;
    /*
    for(int i = 0; i < nums.size(); ++i) nums[i] *= 2.f; // аналогично с остальными
    */
    float a;
    std::cout << "Напишите a: ";
    std::cin >> a;
    for(auto& num : nums) num -= a;
    auto tmp = nums.front(); // ~ nums[0] ~ nums.at(0)
    for(auto& num : nums) num /= tmp;
    for(const auto num : nums){
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void second_func(){
    auto nums = generate_random_vector<float>(25,-100.f,100.f);
    for(const auto num : nums){ // можно было вывод через лямбду сделать, либо иные стандартные функции
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // std::accumulate конечно можно, но не в этом суть сейчас
    {
        auto sum = 0.f;
        for(const auto n : nums){
            sum += n;
        }
        std::cout << sum << std::endl;
    }
    {
        auto sum = 0.f;
        for(const auto n : nums){
            sum += n*n; // n*n ~ std::pow(n,2.f)
        }
        std::cout << sum << std::endl;
    }
    {
        auto sum = 0.f;
        for(int i = 0; i < 6; ++i){ // 0 1 2 3 4 5
            sum += nums[i];
        }
        std::cout << sum << std::endl;
    }
    {
        int k1, k2;
        std::cin >> k1 >> k2;
        auto sum = 0.f;
        for(auto i = k1; i < k2; i++){
            //Если начинаем с 0, то можно не вычитать 1
            sum += nums.at(i); // так безопаснее
        }
        std::cout << sum << std::endl;
    }
    {
        auto sum = 0.f;
        for(const auto n : nums){
            sum += n;
        }
        sum /= nums.size();
        std::cout << sum << std::endl;
    }
    {
        int s1, s2;
        std::cin >> s1 >> s2;
        auto sum = 0.f;
        for(auto i = s1; i < s2; i++){
            sum += nums.at(i);
        }
        sum /= (s2 - s1);
        std::cout << sum << std::endl;
    }
}

void third_func(){
    auto vec = generate_random_vector<int>(20);
    for(const auto num : vec){ // можно было вывод через лямбду сделать, либо иные стандартные функции
        std::cout << num << " ";
    }
    std::cout << std::endl;
    for(auto i = 0; i < 3; ++i){
        // ...#############...
        // =>
        // ABC#############DEF
        // =>
        // DEF#############ABC

        //auto tmp = vec[i];
        //vec[i] = vec[vec.size()-3+i]; // i = 0, 20-3+0=17
        //vec[vec.size()-3+i] = tmp;
        
        vec[i] ^= vec[vec.size()-3+i];
        vec[vec.size()-3+i] ^= vec[i];
        vec[i] ^= vec[vec.size()-3+i];
        //swap интов с помощью битовых операций. A xor B xor B = A 

        // можно было использовать std::swap, но не в этом суть задачи
    }
    for(const auto num : vec){ // можно было вывод через лямбду сделать, либо иные стандартные функции
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
void fourth_func(){
    auto vec = generate_random_vector<int>(20);
    for(const auto num : vec){ // можно было вывод через лямбду сделать, либо иные стандартные функции
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::vector<int> other = {};
    bool flag1 = false;
    for(auto i = 0; i < vec.size(); ++i){
        //можно конечно использовать erase, но не в этом суть
        if(vec.at(i) < 0 && !flag1){
            flag1 = !flag1;
            continue;
        }
        other.push_back(vec.at(i));
    }
    vec = other;
    other.clear();
    flag1 = false;
    for(auto i = 0; i < vec.size(); ++i){ //в std имеются find_first_of, find_last_of и т.д. , но в этом суть задачи
        auto t = vec.size() - i - 1;
        if(vec.at(t) % 2 == 0 && !flag1){
            flag1 = !flag1;
            continue;
        }
        other.push_back(vec.at(t));
    }
    vec = other;
    other.clear();
    for(auto i = 0; i < vec.size(); ++i){
        auto t = vec.size() - 1 - i;
        other.push_back(vec.at(t)); // можно было и через reverse, но не в этом суть
    }
    vec = other;

    for(const auto num : vec){ // можно было вывод через лямбду сделать, либо иные стандартные функции
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

const unsigned int str_len(const char* line){
    unsigned int counter = 0;
    for(char* ptr = (char*)line; *ptr; ++ptr){
        counter++;
    }
    return counter;
}

void fifth_func(){
    std::string name;
    std::cin >> name;
    std::cout << ((str_len(name.c_str()) % 2 == 0) ? "Четно\n" : "Нечётно\n"); // length и size имеют маленькие отличия
}

void sixth_func(){
    std::string name1, name2;
    std::cin >> name1 >> name2;
    auto a = str_len(name1.c_str());
    auto b = str_len(name2.c_str());
    if(a > b){
        std::cout << "1 фамилия длинее 2\n";
    }
    else if(a == b){
        std::cout << "1 фамилия имеет ту же длину, что и 2\n";
    }
    else {
        std::cout << "1 фамилия короче 2\n";
    }
}

void seventh_func(){
    std::string cities[3];
    for(auto i = 0; i < 3; ++i){
        std::cin >> cities[i];
    }
    std::string bigger_len = cities[0];
    std::string smaller_len = cities[0];
    for(auto i = 0; i < 3; ++i){
        if(str_len(bigger_len.c_str()) < str_len(cities[i].c_str())){ // length и size имеют маленькие отличия
            bigger_len = cities[i];
        }
        if(str_len(smaller_len.c_str()) > str_len(cities[i].c_str())){ // length и size имеют маленькие отличия
            smaller_len = cities[i];
        }
    }
    std::cout << bigger_len << " " << smaller_len << std::endl;
}

void eighty_func(){
    int m, n;
    std::cin >> m >> n;
    std::string line;
    std::cin >> line;
    for(auto i = m; i < n; i++){
        std::cout << line.at(i);
    }
}
void nineth_func(){
    std::string word;
    std::cin >> word;
    std::string sub_string = word;
    for(auto& i : sub_string){
        i = '*';
    }
    word = sub_string + word + sub_string;
    std::cout << word << std::endl;
}

void tenth_func(){
    std::string big_line = "";
    std::getline(std::cin,big_line,'\n'); // Trick fix
    std::getline(std::cin,big_line,'\n');
    
    auto count = 0;
    for(const auto i : big_line){
        if(i=='a'){
            count++;
        }
    }
    std::cout << 100.f * (static_cast<float>(count) / str_len(big_line.c_str())) << "%\n";
}

void eleventh_func(){
    std::string newWord, res;
    std::cin >> newWord;

    std::string can_word = "can";

    std::string big_line = "";
    std::getline(std::cin,big_line);
    std::getline(std::cin,big_line);
    
    for(auto i = 0; i < big_line.size(); i++){
        bool found = true;
        for(auto j = 0; j < can_word.size(); j++){
            if(i+j >= big_line.size()){
                found = false;
                break;
            }
            if(big_line[i+j] != can_word[j]){
                found = false;
                break;
            }
        }
        if(found){ // нашли паттерн, проверка, что слово свободно и не входит в другие слова
            if(i-1>=0 && i + can_word.size() < big_line.size()){
                found = (big_line[i-1]==' ' && big_line[i + can_word.size()] == ' ');
            }
            else if (i == 0 && can_word.size() < big_line.size()){
                found = (big_line[can_word.size()] == ' ');
            }
            else if (i + can_word.size() == big_line.size()){
                found = (big_line[i-1] == ' ');
            }
            else{
                found = false;
            }
        }

        if(found){
            res += newWord + " ";
            i += can_word.size();
        }
        else{
            res += big_line[i];
        }
    }
    std::cout << res << std::endl;
}

int main() {
    unsigned int choose;
    std::cout << "Введите номер задания: ";
    std::cin >> choose;
    //можно было здесь создать vector из std::functional<void> и чисто обращаться и вызывать их
    switch (choose)
    {
    case 1:
        first_func();
        break;
    case 2:
        second_func();
        break;
    case 3:
        third_func();
        break;
    case 4:
        fourth_func();
        break;
    case 5:
        fifth_func();
        break;
    case 6:
        sixth_func();
        break;
    case 7:
        seventh_func();
        break;
    case 8:
        eighty_func();
        break;
    case 9:
        nineth_func();
        break;
    case 10:
        tenth_func();
        break;
    case 11:
        eleventh_func();
        break;
    default:
        break;
    }
}