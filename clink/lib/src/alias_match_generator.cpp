// Copyright (c) 2016 Martin Ridgers
// License: http://opensource.org/licenses/MIT

#include "pch.h"
#include "match_generator.h"
#include "line_state.h"
#include "matches.h"

#include <host/doskey.h>

//------------------------------------------------------------------------------
static class _alias_match_generator : public match_generator
{
public:

    virtual bool generate(const line_state& line, match_builder& builder) override
    {
        if (has_alias(line))
        {
            auto new_line = expand_line(line);
            return m_lua->generate(new_line, builder);
        }

        return false;
    }

    virtual void get_word_break_info(const line_state& line, word_break_info& info) const override
    {
        if (has_alias(line))
        {
            auto new_line = expand_line(line);
            m_lua->get_word_break_info(new_line, info);
        }
    }

    void set_lua(match_generator* lua)
    {
        m_lua = lua;
    }

private:
    match_generator* m_lua;
    mutable std::vector<word> new_words;
    mutable str<288> buf;

    static bool has_alias(const line_state& line)
    {
        for (const auto& w : line.get_words())
        {
            if (w.is_alias)
                return true;
        }

        return false;
    }

    line_state expand_line(const line_state& line) const
    {
        // XXX: fake line_state
        new_words.clear();
        new_words.push_back({
            0,
            3,
            true,
            false,
            false,
            ' '
        });

        new_words.push_back({
            4,
            8,
            false,
            false,
            false,
            ' '
        });

        new_words.push_back({
            13,
            0,
            false,
            false,
            false,
            ' '
        });

        buf.clear();
        buf << "git checkout ";

        return {
            buf.c_str(),
            13,
            0,
            new_words
        };
    }
} g_alias_match_generator;


//------------------------------------------------------------------------------
match_generator& alias_match_generator(match_generator& lua)
{
    // XXX: inject alias
    doskey doskey("cmd.exe");
    doskey.add_alias("gco", "git checkout $*");

    g_alias_match_generator.set_lua(&lua);
    return g_alias_match_generator;
}
