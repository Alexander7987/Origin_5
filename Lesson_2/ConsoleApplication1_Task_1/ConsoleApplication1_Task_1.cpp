#include <string>
#include <iostream>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text(text) {}
    Text* text;
};


class Paragraph : public DecoratedText
{
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render (const std::string& data) const override  {
        std::cout << "<p>";
        text->render(data);
        std::cout << "</p>";
    }
};


class Reversed : public DecoratedText
{
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::string temp_string = data; //нужно создать временный неконстантный объект, иначе reverse не сработает
        std::reverse(temp_string.begin(), temp_string.end());
        text->render(temp_string);
    }
};

class Link : public DecoratedText
{
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string link, const std::string data) //т.к. сигнатура отличается, то не пишем override
    {
        std::cout << "<a href=" << link << ">";
        text->render(data);
        std::cout << "</a>";
    }
};


int main() {
    auto text_block1 = new Reversed(new Paragraph(new Text()));
    text_block1->render("Hello world");
    std::cout << std::endl;
    auto text_block2 = new Link(new Text());
    text_block2->render("netology.ru", "Hello world");
}