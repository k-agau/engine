#ifndef VISITOR_H
#define VISITOR_H

class Cube;
class Plane;

class Visitor {
public:
	virtual void visit(const Cube& obj) = 0;
	virtual void visit(const Plane& obj) = 0;
};

#endif // VISITOR_H