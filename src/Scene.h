#pragma once
#include <initializer_list>
#include <memory> 
#include "Camera.h"
#include "Object.h"
class Scene {
	using SharedCamera = std::shared_ptr<Camera>; 
	using SharedObject = std::shared_ptr<Object>; 
private:
	std::vector<SharedObject> SceneObjects; 
	std::vector<SharedCamera> SceneCameras; // Main camera is alwyas the 0th element
	std::vector<SharedObject>::iterator GetObjectIter(const SharedObject& object) {
		std::vector<SharedObject>::iterator iter = SceneObjects.begin(); 
		while (iter != SceneObjects.end()) {
			if (object.get() == iter->get()) {
				return iter; 
			}
			iter++; 
		}
		return SceneObjects.end(); 
	};
	std::vector<SharedCamera>::iterator GetCameraIter(const SharedCamera& camera) {
		std::vector<SharedCamera>::iterator iter = SceneCameras.begin(); 
		while (iter != SceneCameras.end()) {
			if (camera.get() == iter->get()) {
				return iter; 
			}
			iter++; 
		}
		return SceneCameras.end(); 
	};

public: 
	Scene() = default; 
	~Scene(); 
	Scene(const SharedCamera& MainCamera) : SceneCameras{ MainCamera } {} ;
	Scene(const std::initializer_list<SharedObject>&  objs, const std::initializer_list<SharedCamera>&  cameras) : SceneCameras{ cameras }, SceneObjects{ objs } {};
	bool DeleteCamera(const SharedCamera& camera); 
	bool DeleteObject(const SharedObject& object); 
	bool AddCamera(const SharedCamera& camera);
	void AddObject(const SharedObject& object); 
	void MakeMainCamera(const SharedCamera& camera);
	void MakeMainCamera(int cameraindex);
	SharedCamera& GetMainCamera() { return SceneCameras[0];  }
	std::vector<SharedObject>& GetObjects() { return SceneObjects;  }
	std::vector<SharedCamera>& GetCameras() { return SceneCameras;  }
};
