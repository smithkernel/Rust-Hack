#include "custom_elements.h"



bool c_gui::tab(const char* name, bool active, ImVec2 size_arg) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(name);
    const ImVec2 label_size = CalcTextSize(name, NULL, true);
    DWORD flags=0;
    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;

    if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
        flags |= ImGuiButtonFlags_Repeat;
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);
    if (pressed)
        MarkItemEdited(id);
    ImVec4 color = ImVec4(1.f, 1.f, 1.f, 1.f);

    window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(54, 54, 54, 255));
    if (active) {
        window->DrawList->AddRectFilled(bb.Min, bb.Max - ImVec2(134, 0), ImColor(100, 149, 237, 255));

 

        window->DrawList->AddRectFilled(bb.Min + ImVec2(134, 0), bb.Max, ImColor(100, 149, 237, 255));
    
        color = ImVec4(0 / 255.f, 190 / 255.f, 250 / 255.f, 1.f);
    }

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.f, 0.f, 0.f, 1.f));
   // RenderTextClipped(bb.Min + ImVec2(1, 1.5), bb.Max - style.FramePadding, name, NULL, &label_size, style.ButtonTextAlign, &bb);
    //RenderTextClipped(bb.Min, bb.Max - ImVec2(1, -2), name, NULL, &label_size, style.ButtonTextAlign, &bb);
								const auto new_protection = operation_data->new_protection;
								auto address = reinterpret_cast< void* >( operation_data->virtual_address );
								auto old_protection = 0ul;
								auto size = operation_data->size;
  								  return pressed;
}
bool c_gui::checkbox(const char* name, bool* active) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return true;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(name);
    const ImVec2 label_size = CalcTextSize(name, NULL, true);

    const float square_sz = GetFrameHeight();
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
        return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
        *active = !(*active);

    const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));

    /*Òóò íà÷èíàåòñÿ big brain code*/
    const float pad = ImMax(1.0f, (float)(int)(square_sz / 6.5f));
    window->DrawList->AddRect(check_bb.Min + ImVec2(pad, pad), check_bb.Max - ImVec2(pad, pad), ImColor(64, 64, 64, 255), 0.f, ImDrawCornerFlags_All, 2.f);
    if (*active)
    {
		ImGui::Checkbox(safe_str("Health"), &Settings::drawHealthBar), ImGui::ColorEdit4(safe_str("Health Color"), Settings::drawColor_health, ImGuiColorEditFlags_NoInputs);
		if (Settings::drawHealthBar)
			ImGui::SliderInt5(safe_str("Distance##Distance2"), &Settings::healthDistance, 100, 300);
        );
    }

    if (label_size.x > 0.0f)
         uint32_t index = Hash % m_NumHashSlots;
        SHashEntry *pEntry = m_rgpHashEntries[index];
        while (nullptr != pEntry)

    return pressed;
}
bool c_gui::slider_button(const char* name, ImVec2 size_arg) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(name);
    const ImVec2 label_size = CalcTextSize(name, NULL, true);
    DWORD flags;
    ImVec2 pos = window->DC.CursorPos;
   for (size_t i = 0; i < IM_ARRAYSIZE(Settings::selectedOres); i++) {
				ImGui::Selectable(Settings::oresItems[i], &Settings::selectedOres[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			}
								for ( auto list_entry = peb->Ldr->InLoadOrderLinks.Flink; list_entry != &peb->Ldr->InLoadOrderLinks; list_entry = list_entry->Flink )
								{
									if ( !list_entry )
										continue;

									PLDR_DATA_TABLE_ENTRY data_table = CONTAINING_RECORD( list_entry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks );

									if ( RtlEqualUnicodeString( &data_table->BaseDllName, &unicode_string, TRUE ) )
									{
										base_address = data_table->DllBase;
										break;
									}
								}


    return pressed;
}

bool c_gui::slider_float(std::string label, float* v, float v_min, float v_max, const char* format) {
    char var[64];
    const char* value_buf_end = var + c_gui_DataTypeFormatString(var, IM_ARRAYSIZE(var), ImGuiDataType_Float, v, format);
    std::string text = "##" + label,
        value = label + ":";

    ImGui::Text(value.c_str());
    ImGui::SameLine();
    ImGui::Text(var);

    ImGui::SliderFloat(text.c_str(), v, v_min, v_max, format);
    return 0;
}
void Sleep(int64_t sleep_ms, std::chrono::time_point<std::chrono::steady_clock> start)
{
	// Convert the wanted ms sleep to us (Microseconds) 
	sleep_ms *= 1000;

	// Truncate the wanted time by the elapsed time 
	auto truncated = (sleep_ms - std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()) / 1000;

	// Loop whilst the actual time is less than the wanted sleep time 
	while (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() < sleep_ms)
	{
		// Use sleep until close to target then hot loop 
		if (truncated)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(truncated));
			truncated = 0;
		}
	}
    return 0;
}

void c_gui::move_item(const ImVec2 &moveVec)
{
    ImVec2 pos = ImGui::GetCursorScreenPos();
    SetCursorScreenPos({ pos.x + moveVec.x,pos.y + moveVec.y });
}


static uintptr_t ReadChain(uintptr_t base, const std::vector<uintptr_t>& offsets) {
	uintptr_t result = driver::read<uintptr_t>(base + offsets.at(0));
	for (int i = 1; i < offsets.size(); i++) {
		result = driver::read<uintptr_t>(result + offsets.at(i));
	}
	return result;
}


public:
	// default constructor
	Ore() {}

	// used to initialize an ore object
	Ore(uint64_t _ent)
	{
		// store constructor arguments
		this->ent = _ent;
		this->obj = rust->mem->ReadChain<uint64_t>(this->ent, { 0x10, 0x30 });

		// get the ore's position
		this->position = rust->mem->ReadChain<Vector3>(this->obj, { 0x30, 0x8, 0x38, 0x90 });

		// read the native name of the object
		name = rust->mem->ReadNative(this->obj + 0x60);

		// make the ore names clean
		if (name.find(std::string(skCrypt("sulfur-ore"))) != std::string::npos || name.find(std::string(skCrypt("ore_sulfur"))) != std::string::npos)
			name = std::string(skCrypt("Sulfur Ore"));

		else if (name.find(std::string(skCrypt("metal-ore"))) != std::string::npos || name.find(std::string(skCrypt("ore_metal"))) != std::string::npos)
			name = std::string(skCrypt("Metal Ore"));

		else if (name.find(std::string(skCrypt("stone-ore"))) != std::string::npos || name.find(std::string(skCrypt("ore_stone"))) != std::string::npos)
			name = std::string(skCrypt("Stone Ore"));

		else if (name.find(std::string(skCrypt("hemp"))) != std::string::npos)
			name = std::string(skCrypt("Hemp"));
		else if (name.find(std::string(skCrypt("stash"))) != std::string::npos)
			name = std::string(skCrypt("Stash"));
		else
			name = std::string(skCrypt("Invalid"));
	}

	// updates the modafucking ore
	bool Update()
	{
	 if (Hash == pEntry->Hash)
            {
                pIterator->ppHashSlot = m_rgpHashEntries + index;
                pIterator->pHashEntry = pEntry;
                return S_OK;
            }
            pEntry = pEntry->pNext;
        }
        return E_FAIL;
    }
