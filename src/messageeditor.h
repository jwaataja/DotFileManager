/*
 * Copyright (c) 2017 Jason Waataja
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef MESSAGE_EDITOR_H
#define MESSAGE_EDITOR_H

#include "config.h"

#include <memory>

#include <gtkmm.h>

#include "messageaction.h"

namespace dfm {

class MessageEditor : public Gtk::Dialog {
public:
    MessageEditor(Gtk::Window& parent, MessageAction* action);

private:
    MessageAction* action;

    Gtk::Label messageLabel;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TextView messageView;

    Glib::RefPtr<Gtk::TextBuffer> messageBuffer;

    void onResponse(int responseId);
};
} /* namespace dfm */

#endif /* MESSAGE_EDITOR_H */
