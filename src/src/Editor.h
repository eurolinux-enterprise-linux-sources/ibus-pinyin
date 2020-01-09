/* vim:set et ts=4 sts=4:
 *
 * ibus-pinyin - The Chinese PinYin engine for IBus
 *
 * Copyright (c) 2008-2010 Peng Huang <shawn.p.huang@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifndef __PY_EDITOR_H_
#define __PY_EDITOR_H_

#include <glib.h>
#include <boost/shared_ptr.hpp>
#include "Signal.h"
#include "String.h"
#include "Text.h"
#include "LookupTable.h"
#include "PinyinProperties.h"
#include "Config.h"
#include "Util.h"

namespace PY {

class Editor;
typedef boost::shared_ptr<Editor> EditorPtr;

class Editor {
public:
    Editor (PinyinProperties & prop, Config & config);
    virtual ~Editor (void);

    virtual gboolean processKeyEvent (guint keyval, guint keycode, guint modifiers);
    virtual void pageUp (void);
    virtual void pageDown (void);
    virtual void cursorUp (void);
    virtual void cursorDown (void);
    virtual void update (void);
    virtual void reset (void);
    virtual void candidateClicked (guint index, guint button, guint state);

    const String & text (void) const { return m_text; }
    void setText (const String & text, guint cursor) {
        m_text = text;
        m_cursor = cursor;
    }

    /* signals */
    signal <void (Text &)> & signalCommitText (void) { return m_signal_commit_text; }
    signal <void (Text &, guint, gboolean)> & signalUpdatePreeditText (void) { return m_signal_update_preedit_text; }
    signal <void ()> & signalShowPreeditText (void) { return m_signal_show_preedit_text; }
    signal <void ()> & signalHidePreeditText (void) { return m_signal_hide_preedit_text; }
    signal <void (Text &, gboolean)> & signalUpdateAuxiliaryText (void) { return m_signal_update_auxiliary_text; }
    signal <void ()> & signalShowAuxiliaryText (void) { return m_signal_show_auxiliary_text; }
    signal <void ()> & signalHideAuxiliaryText (void) { return m_signal_hide_auxiliary_text; }
    signal <void (LookupTable &, gboolean)> & signalUpdateLookupTable (void) { return m_signal_update_lookup_table; }
    signal <void (LookupTable &, gboolean)> & signalUpdateLookupTableFast (void) { return m_signal_update_lookup_table_fast; }
    signal <void ()> & signalShowLookupTable (void) { return m_signal_show_lookup_table; }
    signal <void ()> & signalHideLookupTable (void) { return m_signal_hide_lookup_table; }

protected:
    /* methods */
    void commitText (Text & text) {
        m_signal_commit_text (text);
    }

    void updatePreeditText (Text & text, guint cursor, gboolean visible) {
        m_signal_update_preedit_text (text, cursor, visible);
    }

    void showPreeditText (void) {
        m_signal_show_preedit_text ();
    }

    void hidePreeditText (void) {
        m_signal_hide_preedit_text ();
    }

    void updateAuxiliaryText (Text & text, gboolean visible) {
        m_signal_update_auxiliary_text (text, visible);
    }

    void showAuxiliaryText (void) {
        m_signal_show_auxiliary_text ();
    }

    void hideAuxiliaryText (void) {
        m_signal_hide_auxiliary_text ();
    }

    void updateLookupTable (LookupTable & table, gboolean visible) {
        m_signal_update_lookup_table (table, visible);
    }

    void updateLookupTableFast (LookupTable & table, gboolean visible) {
        m_signal_update_lookup_table_fast (table, visible);
    }

    void showLookupTable (void) {
        m_signal_show_lookup_table ();
    }

    void hideLookupTable (void) {
        m_signal_hide_lookup_table ();
    }

protected:
    /* signals */
    signal <void (Text &)> m_signal_commit_text;
    signal <void ( Text &, guint, gboolean)> m_signal_update_preedit_text;
    signal <void ()> m_signal_show_preedit_text;
    signal <void ()> m_signal_hide_preedit_text;
    signal <void (Text &, gboolean)> m_signal_update_auxiliary_text;
    signal <void ()> m_signal_show_auxiliary_text;
    signal <void ()> m_signal_hide_auxiliary_text;
    signal <void (LookupTable &, gboolean)> m_signal_update_lookup_table;
    signal <void (LookupTable &, gboolean)> m_signal_update_lookup_table_fast;
    signal <void ()> m_signal_show_lookup_table;
    signal <void ()> m_signal_hide_lookup_table;

protected:
    String m_text;
    guint  m_cursor;
    PinyinProperties & m_props;
    Config & m_config;
};

};

#endif
