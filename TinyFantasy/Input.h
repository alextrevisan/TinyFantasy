#ifndef INPUT_H
#define INPUT_H

class Input
{
    public:
        enum KEYS
        {
            UP = 0,
            DOWN = 1,
            LEFT = 2,
            RIGHT = 3,
            USE = 4
        };
        static void readKeys();
        static bool isKeyDown(int key);
    protected:
    private:
        static bool keyDown[5];
};

#endif // INPUT_H
