#include "Scene.h"



Scene::~Scene()
{
	for (SharedCamera& a : SceneCameras) {
		a.reset(); 
	}
	for (SharedObject& a : SceneObjects) {
		a.reset(); 
	}

}
bool Scene::DeleteCamera(const SharedCamera& camera)
{
	if (GetCameraIter(camera) != SceneCameras.end()) {
		SceneCameras.erase(GetCameraIter(camera)); 
		return true; 
	}
	return false;
}

bool Scene::DeleteObject(const SharedObject& object)
{

	if (GetObjectIter(object) != SceneObjects.end()) {
		SceneObjects.erase(GetObjectIter(object));
		return true; 
	}
	return false;
}

bool Scene::AddCamera(const SharedCamera& camera)
{
	if (GetCameraIter(camera) != SceneCameras.end()) {
		SceneCameras.push_back(camera);
		return true; 
	}
	return false; 
}


void Scene::AddObject(const SharedObject& object)
{
	if (GetObjectIter(object) != SceneObjects.end()) {
		SceneObjects.push_back(object);
	}
}

void Scene::MakeMainCamera(const SharedCamera& camera)
{
	AddCamera(camera); 
	auto iter = GetCameraIter(camera); 
	std::rotate(SceneCameras.begin(), iter, SceneCameras.end()); 
}

void Scene::MakeMainCamera(int cameraindex)
{
	if (cameraindex != 0) {
		std::rotate(SceneCameras.begin(), SceneCameras.begin() + cameraindex, SceneCameras.end()); 
	}
}
