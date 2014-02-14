class Observer
{
public:
	virtual void update() = 0;
};

class Subject
{
public:
	virtual void addObserver(Observer obs);
	virtual void notify();
private:
	Observer obs;
};

class OneObserver : public Observer
{
public:
	virtual void update();
};
