#pragma once

namespace Omega::Graphics
{
	class Model;

	class Animator
	{
	public:
		void Initialize(const Model& model);
		void Terminate();

		void ComputeBindPose();
		void PlayAnimation(int index);

		void StopAnimation(bool stop);
		void SetTime(float time);

		void Update(float deltaTime);

		inline auto& GetBoneMatrices() const { return mBoneMatrices; }
		inline auto& GetBoneMatricesFinalTransform() const { return mBoneMatricesFinal; }

		inline float GetMaxDuration() const { return mMaxDuration; }

		inline void ShowSkeleton(bool show) { mShowSkeleton = show; }
	private:
		const Model* mModel;
		float mMaxDuration = 0.0f;
		float mTimer = 0.0f;
		float mCurrentTimer = 0.0f;
		int mClipIndex = 0;
		bool mShowSkeleton = false;

		std::vector<Omega::Math::Matrix4> mBoneMatrices;
		Omega::Math::Matrix4 mBoneMatricesFinal[128];
	};

}