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

		void Update(float deltaTime);

		inline auto& GetBoneMatrices() const { return mBoneMatrices; }
	private:
		const Model* mModel;
		float mTimer = 0.0f;
		int mClipIndex = 0;

		std::vector<Omega::Math::Matrix4> mBoneMatrices;
	};

}