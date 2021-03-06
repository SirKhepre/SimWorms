#include "Transformable.h"


sdl::Transformable::Transformable()
{
	orientation = 0;
	position = sdl::Vector2Float(0, 0);
	origin = sdl::Vector2Float(0, 0);
	scaleFactors = sdl::Vector2Float(1, 1);
	flipSide = SDL_FLIP_NONE;
}

sdl::Transformable::~Transformable()
{
}

void sdl::Transformable::setPosition(float x, float y){
	this->position = sdl::Vector2Float(x, y);
}
void sdl::Transformable::setPosition(sdl::Vector2Float &position){
	this->position = position;
}

void sdl::Transformable::setScale(float factorX, float factorY){
	this->scaleFactors = sdl::Vector2Float(factorX, factorY);
}
void sdl::Transformable::setScale(sdl::Vector2Float &factors){
	this->scaleFactors = factors;
}

void sdl::Transformable::setRotation(float angle){
	this->orientation = angle;
}

void sdl::Transformable::setOrigin(float x, float y){
	this->origin = sdl::Vector2Float(x, y);
}
void sdl::Transformable::setOrigin(sdl::Vector2Float &origin){
	this->origin = origin;
}

sdl::Vector2Float& sdl::Transformable::getPosition(){
	return this->position;
}

float sdl::Transformable::getRotation(){
	return this->orientation;
}

sdl::Vector2Float& sdl::Transformable::getScale(){
	return this->scaleFactors;
}
sdl::Vector2Float& sdl::Transformable::getOrigin(){
	return this->origin;
}

void sdl::Transformable::move(float x, float y){
	this->position.x += x;
	this->position.y += y;
}
void sdl::Transformable::move(sdl::Vector2Float &vect){
	this->position.x += vect.x;
	this->position.y += vect.y;
}

void sdl::Transformable::rotate(float angle){
	this->orientation += angle;
}

void sdl::Transformable::scale(float factorX, float factorY){
	this->scaleFactors.x = factorX;
	this->scaleFactors.y = factorY;
}
void sdl::Transformable::scale(sdl::Vector2Float &factors){
	this->scaleFactors.x = factors.x;
	this->scaleFactors.y = factors.y;
}

void sdl::Transformable::flip(SDL_RendererFlip flip){
	this->flipSide = flip;
}

sdl::RectFloat sdl::Transformable::getRenderDestination(sdl::View& view) {
	std::vector<float> components;
	Vector2Float viewRatio = { view.getViewport().w / view.getSize().x, view.getViewport().h / view.getSize().y };
	for (int i = 0; i < 2; ++i) {
		float truePosition = position[i] - origin[i];
		float viewBound = view.getCenter()[i] - view.getSize()[i] / 2;
		float viewScaledPosition = (truePosition - viewBound) * viewRatio[i];
		components.push_back(viewScaledPosition);
	} for (int i = 0; i < 2; ++i) {
		float scaledTexturePosition = bounds[i + 2] * scaleFactors[i];
		float viewScaled = scaledTexturePosition * viewRatio[i];
		components.push_back(viewScaled);
	} return sdl::RectFloat(components[0], components[1], components[2], components[3]);
}