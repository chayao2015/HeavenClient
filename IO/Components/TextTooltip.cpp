//////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright © 2015-2016 Daniel Allendorf                                   //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "TextTooltip.h"

#include "../Constants.h"

#include "../../Data/ItemData.h"

#include "nlnx/nx.hpp"
#include "nlnx/node.hpp"

namespace jrc
{
	TextTooltip::TextTooltip()
	{
		nl::node Frame = nl::nx::ui["UIToolTip.img"]["Item"]["Frame2"];

		frame = Frame;
		cover = Frame["cover"];

		text = "";

		fillwidth = 340;
	}

	void TextTooltip::draw(Point<int16_t> pos) const
	{
		if (text_label.empty())
			return;

		int16_t fillheight = text_label.height();

		int16_t max_width = Constants::Constants::get().get_viewwidth();
		int16_t max_height = Constants::Constants::get().get_viewheight();
		int16_t cur_width = pos.x() + fillwidth + 21;
		int16_t cur_height = pos.y() + fillheight + 40;

		int16_t adj_x = cur_width - max_width;
		int16_t adj_y = cur_height - max_height;

		if (adj_x > 0)
			pos.shift_x(adj_x * -1);

		if (adj_y > 0)
			pos.shift_y(adj_y * -1);

		frame.draw(pos + Point<int16_t>(190, 7), fillwidth - 28, fillheight - 18);
		cover.draw(pos + Point<int16_t>(20, -22));
		text_label.draw(pos + Point<int16_t>(25, -20));
	}

	bool TextTooltip::set_text(std::string t)
	{
		if (text == t)
			return false;

		text = t;

		if (text.empty())
			return false;

		text_label = Text(Text::Font::A12M, Text::Alignment::LEFT, Text::Color::WHITE, text, fillwidth, true, 2);

		return true;
	}
}