//
//  SceneChanger.hpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/09/20.
//
//

#ifndef __coconut_SceneChanger__
#define __coconut_SceneChanger__

#include "cocos2d.h"

namespace coconut {
	
	class SceneChanger {
	private:
		bool _push;
	protected:
		SceneChanger(bool push = false) : _push(push) {
		}
		void runWith(cocos2d::Scene* scene) const {
			cocos2d::Director::getInstance()->runWithScene(scene);
		}
		void replace(cocos2d::Scene* scene) const {
			if (_push) {
				cocos2d::Director::getInstance()->pushScene(scene);
			} else {
				cocos2d::Director::getInstance()->replaceScene(scene);
			}
		}
	public:
		virtual void changeTo(cocos2d::Scene* scene) const = 0;
	};
	
	class OverlayScene : public cocos2d::Scene {
	private:
		cocos2d::Scene* _overlay;
		cocos2d::Scene* _prevScene;
		cocos2d::FiniteTimeAction* _action;
		bool shown;
	public:
		OverlayScene(cocos2d::Scene* scene, cocos2d::FiniteTimeAction* action) {
			shown = false;
			_overlay = scene;
			_action = action;
			_overlay->setVisible(false);
			addChild(_overlay, 1);
			_prevScene = cocos2d::Director::getInstance()->getRunningScene();
			_prevScene->retain();
		}
		~OverlayScene() {
			_prevScene->release();
		}
    virtual void onEnter() override {
			_isTransitionFinished = false;
			_overlay->onEnter();
			resume();
			_running = true;
			if (!shown) {
				addChild(_prevScene, 0);
			}
		}
    virtual void onEnterTransitionDidFinish() override {
			_isTransitionFinished = true;
			if (!shown) {
				if (_action) {
					_overlay->runAction(cocos2d::Sequence::create(cocos2d::Show::create(),
																												_action,
																												cocos2d::CallFunc::create([this]() {_overlay->onEnterTransitionDidFinish();}),
																												nullptr));
				} else {
					_overlay->setVisible(true);
					_overlay->onEnterTransitionDidFinish();
				}
				shown = true;
			} else {
				_overlay->onEnterTransitionDidFinish();
			}
		}
		cocos2d::Scene* getOverlayScene() {
			return _overlay;
		}
		cocos2d::Scene* getPrevScene() {
			return _prevScene;
		}
		void destroyStart() {
			_overlay->onExitTransitionDidStart();
		}
		void destroyEnd() {
			removeChild(_overlay);
			removeChild(_prevScene);
		}
		static OverlayScene* create(cocos2d::Scene* scene, cocos2d::FiniteTimeAction* action) {
			OverlayScene* instance = new OverlayScene(scene, action);
			if (instance && instance->init()) {
				instance->autorelease();
				return instance;
			}
			CC_SAFE_DELETE(instance);
			return nullptr;
		}
	};
	
	namespace SceneChangers{
		
		class Initial : public SceneChanger {
		public:
			virtual void changeTo(cocos2d::Scene* scene) const override {
				runWith(scene);
			}
		};
		
		class Normal : public SceneChanger {
		public:
			Normal(bool push = false) : SceneChanger(push) {
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(scene);
			}
		};
		
		class RotoZoom : public SceneChanger {
		private:
			float _duration;
		public:
			RotoZoom(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionRotoZoom::create(_duration, scene));
			}
		};
		
		class JumpZoom : public SceneChanger {
		private:
			float _duration;
		public:
			JumpZoom(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionJumpZoom::create(_duration, scene));
			}
		};
		
		class MoveInL : public SceneChanger {
		private:
			float _duration;
		public:
			MoveInL(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionMoveInL::create(_duration, scene));
			}
		};
		
		class MoveInR : public SceneChanger {
		private:
			float _duration;
		public:
			MoveInR(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionMoveInR::create(_duration, scene));
			}
		};
		
		class MoveInT : public SceneChanger {
		private:
			float _duration;
		public:
			MoveInT(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionMoveInT::create(_duration, scene));
			}
		};
		
		class MoveInB : public SceneChanger {
		private:
			float _duration;
		public:
			MoveInB(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionMoveInB::create(_duration, scene));
			}
		};
		
		class SlideInL : public SceneChanger {
		private:
			float _duration;
		public:
			SlideInL(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionSlideInL::create(_duration, scene));
			}
		};
		
		class SlideInR : public SceneChanger {
		private:
			float _duration;
		public:
			SlideInR(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionSlideInR::create(_duration, scene));
			}
		};
		
		class SlideInT : public SceneChanger {
		private:
			float _duration;
		public:
			SlideInT(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionSlideInT::create(_duration, scene));
			}
		};
		
		class ShrinkGrow : public SceneChanger {
		private:
			float _duration;
		public:
			ShrinkGrow(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionShrinkGrow::create(_duration, scene));
			}
		};
		
		class FlipL : public SceneChanger {
		private:
			float _duration;
		public:
			FlipL(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFlipX::create(_duration, scene,
																								 cocos2d::TransitionScene::Orientation::LEFT_OVER));
			}
		};
		
		class FlipR : public SceneChanger {
		private:
			float _duration;
		public:
			FlipR(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFlipX::create(_duration, scene,
																								 cocos2d::TransitionScene::Orientation::RIGHT_OVER));
			}
		};
		
		class FlipU : public SceneChanger {
		private:
			float _duration;
		public:
			FlipU(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFlipY::create(_duration, scene,
																								 cocos2d::TransitionScene::Orientation::UP_OVER));
			}
		};
		
		class FlipD : public SceneChanger {
		private:
			float _duration;
		public:
			FlipD(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFlipY::create(_duration, scene,
																								 cocos2d::TransitionScene::Orientation::DOWN_OVER));
			}
		};
		
		class FlipAngularL : public SceneChanger {
		private:
			float _duration;
		public:
			FlipAngularL(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFlipAngular::create(_duration, scene,
																											 cocos2d::TransitionScene::Orientation::LEFT_OVER));
			}
		};
		
		class FlipAngularR : public SceneChanger {
		private:
			float _duration;
		public:
			FlipAngularR(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFlipAngular::create(_duration, scene,
																											 cocos2d::TransitionScene::Orientation::RIGHT_OVER));
			}
		};
		
		class ZoomFlipL : public SceneChanger {
		private:
			float _duration;
		public:
			ZoomFlipL(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionZoomFlipX::create(_duration, scene,
																										 cocos2d::TransitionScene::Orientation::LEFT_OVER));
			}
		};
		
		class ZoomFlipR : public SceneChanger {
		private:
			float _duration;
		public:
			ZoomFlipR(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionZoomFlipX::create(_duration, scene,
																										 cocos2d::TransitionScene::Orientation::RIGHT_OVER));
			}
		};
		
		class ZoomFlipU : public SceneChanger {
		private:
			float _duration;
		public:
			ZoomFlipU(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionZoomFlipY::create(_duration, scene,
																										 cocos2d::TransitionScene::Orientation::UP_OVER));
			}
		};
		
		class ZoomFlipD : public SceneChanger {
		private:
			float _duration;
		public:
			ZoomFlipD(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionZoomFlipY::create(_duration, scene,
																										 cocos2d::TransitionScene::Orientation::DOWN_OVER));
			}
		};
		
		class ZoomFlipAngularL : public SceneChanger {
		private:
			float _duration;
		public:
			ZoomFlipAngularL(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionZoomFlipAngular::create(_duration, scene,
																													 cocos2d::TransitionScene::Orientation::LEFT_OVER));
			}
		};
		
		class ZoomFlipAngularR : public SceneChanger {
		private:
			float _duration;
		public:
			ZoomFlipAngularR(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionZoomFlipAngular::create(_duration, scene,
																													 cocos2d::TransitionScene::Orientation::RIGHT_OVER));
			}
		};
		
		class Fade : public SceneChanger {
		private:
			float _duration;
			cocos2d::Color3B _color;
		public:
			Fade(float duration, const cocos2d::Color3B& color, bool push = false) : SceneChanger(push) {
				_duration = duration;
				_color = color;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFade::create(_duration, scene, _color));
			}
		};
		
		class CrossFade : public SceneChanger {
		private:
			float _duration;
		public:
			CrossFade(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionCrossFade::create(_duration, scene));
			}
		};
		
		class TurnOffTiles : public SceneChanger {
		private:
			float _duration;
		public:
			TurnOffTiles(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionTurnOffTiles::create(_duration, scene));
			}
		};
		
		class SplitCols : public SceneChanger {
		private:
			float _duration;
		public:
			SplitCols(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionSplitCols::create(_duration, scene));
			}
		};
		
		class SplitRows : public SceneChanger {
		private:
			float _duration;
		public:
			SplitRows(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionSplitRows::create(_duration, scene));
			}
		};
		
		class FadeTR : public SceneChanger {
		private:
			float _duration;
		public:
			FadeTR(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFadeTR::create(_duration, scene));
			}
		};
		
		class FadeBL : public SceneChanger {
		private:
			float _duration;
		public:
			FadeBL(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFadeBL::create(_duration, scene));
			}
		};
		
		class FadeUp : public SceneChanger {
		private:
			float _duration;
		public:
			FadeUp(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFadeUp::create(_duration, scene));
			}
		};
		
		class FadeDown : public SceneChanger {
		private:
			float _duration;
		public:
			FadeDown(float duration, bool push = false) : SceneChanger(push) {
				_duration = duration;
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				replace(cocos2d::TransitionFadeDown::create(_duration, scene));
			}
		};
		
		class Overlay : public SceneChanger {
		private:
			cocos2d::FiniteTimeAction* _action;
		public:
			Overlay(cocos2d::FiniteTimeAction* action = nullptr) : SceneChanger(false), _action(action) {
			}
			virtual void changeTo(cocos2d::Scene* scene) const override {
				OverlayScene* overlay = OverlayScene::create(scene, _action);
				replace(overlay);
			}
		};
		
	}
	
	namespace SceneRestorers {
		
		class Overlay {
		private:
			cocos2d::FiniteTimeAction* _action;
			OverlayScene* getOverlayScene() const {
				return (OverlayScene*)cocos2d::Director::getInstance()->getRunningScene();
			}
			void destroy() const {
				OverlayScene* overlay = getOverlayScene();
				cocos2d::Scene* prevScene = overlay->getPrevScene();
				prevScene->retain();
				overlay->destroyEnd();
				cocos2d::Director::getInstance()->replaceScene(prevScene);
				prevScene->release();
			}
		public:
			Overlay(cocos2d::FiniteTimeAction* action = nullptr) : _action(action) {
			}
			void close() const {
				OverlayScene* overlay = getOverlayScene();
				overlay->destroyStart();
				if (_action) {
					overlay->getOverlayScene()->runAction(cocos2d::Sequence::create(_action,
																																					cocos2d::CallFunc::create([this]() {destroy();}),
																																					nullptr));
				} else {
					destroy();
				}
			}
		};
		
		class StackedScene {
		public:
			void pop() {
				cocos2d::Director::getInstance()->popScene();
			}
			void popToRoot() {
				cocos2d::Director::getInstance()->popToRootScene();
			}
			void popTo(int level) {
				cocos2d::Director::getInstance()->popToSceneStackLevel(level);
			}
		};
		
	}
	
}

#endif /* defined(__coconut_SceneChanger__) */
