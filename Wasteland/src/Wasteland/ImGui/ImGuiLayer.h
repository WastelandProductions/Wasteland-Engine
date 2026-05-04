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

		void OnEvent(Event& event) override;
		
		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}