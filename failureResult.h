#pragma once
#include "sceneState.h"
#include "gameObject.h"
#include "UI.h"
#include "audio.h"

class FailureResult : public SceneState
{
private:
	std::list<GameObject*> m_GameObject[3];
	std::list<UI*> m_Texture;
	Audio* m_BGM{};


public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	template <typename T>	//テンプレート関数
	T* AddGameObject(int Layer) {
		T* gameObject = new T;
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;
	}

	//指定したGameObjectの取得
	template <typename T>
	T* GetGameObject() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				T* ret = dynamic_cast<T*>(object);
				if (ret != nullptr) {
					return ret;
				}
			}
		}
		return nullptr;
	}

	template <class T>
	T* AddUITexture() {
		T* ui = new T;
		m_Texture.push_back(ui);
		ui->SetScene(this);

		return ui;
	}

	template <class T>
	T* GetUITexture() {
		for (UI* ui : m_Texture) {
			T* ret = dynamic_cast<T*>(UI);
			if (ret != nullptr) {
				return ret;
			}
		}
		return nullptr;
	}
};