#include "pch.h"
#include "Animator.h"

#include "Game.h"
#include "TimeManager.h"

Animator::Animator()
	:Super(ComponentType::Animator)
{
}

Animator::~Animator()
{
}

void Animator::Init()
{
}

void Animator::Update()
{
	shared_ptr<Animation> animation = GetCurrentAnimation();
	if (animation == nullptr)
		return;

	const Keyframe& keyframe = animation->GetKeyframe(_currentKeyframeIndex);

	float deltaTime = GGame->GetTimeManager()->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= keyframe.time)
	{
		_sumTime = 0.f;

		_currentKeyframeIndex++;
		int32 totalCount = animation->GetKeyframeCount();

		if (_currentKeyframeIndex >= totalCount)
		{
			if (animation->IsLoop())
				_currentKeyframeIndex = 0;
			else
				_currentKeyframeIndex = totalCount - 1;
		}
	}

}

shared_ptr<Animation> Animator::GetCurrentAnimation()
{
	return _currentAnimation;
}

const Keyframe& Animator::GetCurrentKeyframe()
{
	return _currentAnimation->GetKeyframe(_currentKeyframeIndex);
}