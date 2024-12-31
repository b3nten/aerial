#include "RenderSystem.h"


namespace aerial::core_systems {

	render_system::render_system()
	{
		SDL_GPUDevice* fuck = SDL_CreateGPUDevice(
			SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL,true,NULL);
	}

	void render_system::on_start()
	{
		
	}

	void render_system::on_update()
	{

	}

	void render_system::on_end()
	{

	}

	render_system::~render_system()
	{

	}

}
