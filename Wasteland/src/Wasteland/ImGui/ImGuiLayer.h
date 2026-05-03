#pragma once

#include "Wasteland/Core/Layer.h"

#include <Wasteland/Events/ApplicationEvent.h>
#include <Wasteland/Events/MouseEvent.h>
#include <Wasteland/Events/KeyEvent.h>

namespace Wasteland {

	class WL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}