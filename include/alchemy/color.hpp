#ifndef __COLOR_H__
#define __COLOR_H__

#include "types.hpp"
#include "mathutils.hpp"

#include <sstream>

#define ESCAPE_CODE "\x1B"
#define CODE_DELIM "["
#define ERASE_CODE "2J"
#define ANSII_CODE(x) ESCAPE_CODE CODE_DELIM x

namespace alc
{
	struct Color
    {
        enum Masks : u32
        {
            WHITE = 0x00FFFFFF,
            RED   = 0x00FF0000,
            GREEN = 0x0000FF00,
            BLUE  = 0x000000FF,
            ALPHA = 0xFF000000,
        };  

        enum Modifiers : u8
        {
            NONE = 0x0,
            BOLD = 1 << 1,
            UNDERLINED = 1 << 2,
            STRIKED = 1 << 3,
            ITALIC = 1 << 4,
            DIM = 1 << 5,
            REVERSED = 1 << 6
        };

        u8 r, g, b;
        u8 alpha, modifier_flags = Modifiers::NONE;

        Color(u8 r, u8 g, u8 b) : r(r), g(g), b(b) 
        {
            this->alpha = 0xFF;
        }

        Color(u32 rgb_hex)
        {
            this->alpha = (rgb_hex & Masks::ALPHA) >> 24;
            
            this->r = (rgb_hex & Masks::RED)   >> 16;
            this->g = (rgb_hex & Masks::GREEN) >> 8;
            this->b = (rgb_hex & Masks::BLUE);
        }

        string compile_modifiers()
        {
            std::stringstream ss;

            if (this->modifier_flags & Modifiers::BOLD)
                ss << ANSII_CODE("1m");

            if (this->modifier_flags & Modifiers::UNDERLINED)
                ss << ANSII_CODE("4m");

            if (this->modifier_flags & Modifiers::ITALIC)
                ss << ANSII_CODE("3m");

            return ss.str();
        }

        string as_ansii_fg()
        {
            std::stringstream ss;
            ss << ESCAPE_CODE << CODE_DELIM << "38;2;" << +this->r << ";" << +this->g << ";" << +this->b << "m";
            return this->compile_modifiers() + ss.str(); 
        }

        string as_ansii_bg()
        {
            std::stringstream ss;
            ss << ESCAPE_CODE << CODE_DELIM << "48;2;" << +this->r << ";" << +this->g << ";" << +this->b << "m";
            return this->compile_modifiers() + ss.str(); 
        }

        Color use_mask(u32 hex_mask)
        {
            Color mask_rgb(hex_mask);

            this->r |= mask_rgb.r;
            this->g |= mask_rgb.g;
            this->b |= mask_rgb.b;

            return *this;
        }

        Color use_mask(Color color_mask)
        {
            this->use_mask((u32) color_mask);

            return *this;
        }

        Color copy_from(Color other)
        {
            this->r = other.r;
            this->g = other.g;
            this->b = other.b;
            this->alpha = other.alpha;
            this->modifier_flags = other.modifier_flags;

            return *this;
        }

        Color clone()
        {
            return Color { this->r, this->g, this->b };
        }

        operator u32()
        {
            u32 ret = 
                (this->alpha << 24) +
                (this->r << 16) +
                (this->g << 8) +
                this->b;

            return ret;
        }

        operator string()
        {
            return this->as_ansii_fg();
        }
        
        static string gradient(const string txt, Color start, Color end)
        {
            string gradient_txt;
            size_t input_txt_size = txt.length();

            for (int i = 0; i < input_txt_size; i++)
            {
                f32 t = (f32) (i + 1) / (f32) (input_txt_size);
                // std::cout << "GETTING GRADIENT LERP => " << +i << "/" << +input_txt_size << " = " << t << std::endl;
                Color current_color = Color::lerp(start, end, t);
                char current_char = txt.at(i);

                gradient_txt += current_color.as_ansii_fg() + current_char + Color::reset();
            }

            return gradient_txt;
        }

        static Color lerp(const Color a, const Color b, f32 t)
        {
            Color lerped(Color::Masks::ALPHA);

            lerped.alpha = (u8) LERP_INLINE(a.alpha, b.alpha, t);
            lerped.r     = (u8) LERP_INLINE(a.r, b.r, t);
            lerped.g     = (u8) LERP_INLINE(a.g, b.g, t);
            lerped.b     = (u8) LERP_INLINE(a.b, b.b, t);

            // std::cout << "LERPED R: " << +a.r << " => " << +b.r << +lerped.r << ", T=" << t << std::endl;
            // std::cout << "LERPED G: " << +a.g << " => " << +b.g << +lerped.g << ", T=" << t << std::endl;
            // std::cout << "LERPED B: " << +a.b << " => " << +b.b << +lerped.b << ", T=" << t << std::endl;

            return lerped;
        }

        static string reset()
        {
            return ANSII_CODE("0m");
        }

		static string ForegroundRGB(u8 r, u8 g, u8 b)
		{
			return Color(r, g, b).as_ansii_fg();
		}

		static string BackgroundRGB(u8 r, u8 g, u8 b)
		{
			return Color(r, g, b).as_ansii_bg();
		}
    };
};


#endif // __COLOR_H__