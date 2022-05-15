/*
 * Whatsapp Butler plugin
 *
 * Copyright (c) 2022, Vipin Cherian
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* config.h may define PURPLE_PLUGINS; protect the definition here so that we
 * don't get complaints about redefinition when it's not necessary. */
#ifndef PURPLE_PLUGINS
# define PURPLE_PLUGINS
#endif

#include <glib.h>

#ifndef G_GNUC_NULL_TERMINATED
# if __GNUC__ >= 4
#  define G_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
# else
#  define G_GNUC_NULL_TERMINATED
# endif
#endif

#include <notify.h>
#include <plugin.h>
#include <version.h>
#include <debug.h>

#define DISPLAY_VERSION "1.0"
#define PLUGIN_NAME "Whatsapp Butler"
#define IGN_CONV_TITLE "status@broadcast"

PurplePlugin *wbutler_plugin = NULL;

/*
 * Drops all file transfers
 */
static void
file_recv_request_cb(PurpleXfer *xfer, gpointer handle)
{
    // TODO: Check if the file transfer is from Whatsapp
    xfer->status = PURPLE_XFER_STATUS_CANCEL_LOCAL;
}

/*
 * Drops all status broadcasts
 */
static void
conversation_created_cb(PurpleConversation *conv, void *data)
{
    //purple_debug_misc(PLUGIN_NAME, "conversation-created (%s)\n",
    //    purple_conversation_get_name(conv));

    // TODO: Check if the conversation is from Whatsapp
    if(!strcmp(purple_conversation_get_name(conv), IGN_CONV_TITLE))
    {
        purple_debug_misc(PLUGIN_NAME, "About to delete conversation\n");
        purple_conversation_destroy(conv);
    }

}

static gboolean
plugin_load (PurplePlugin * plugin)
{
    // purple_debug_info("Whatsapp helper plugin: ", "Has loaded");

    wbutler_plugin = plugin;

    /* Hook file transfer */
    purple_signal_connect(
        purple_xfers_get_handle(), "file-recv-request", plugin,
        PURPLE_CALLBACK(file_recv_request_cb), plugin);
    /* Hook creation of conversations */
    purple_signal_connect(
        purple_conversations_get_handle(), "conversation-created",
        plugin, PURPLE_CALLBACK(conversation_created_cb), NULL);

    return TRUE;
}

static PurplePluginInfo info =
{
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    NULL,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,

    "core-whatsapp_butler",
    PLUGIN_NAME,
    DISPLAY_VERSION,
    "Whatsapp Butler Plugin",
    "Whatsapp Butler Plugin",
    "Vipin Cherian",
    "https://github.com/vipincherian/whatsappbutler",


    plugin_load,
    NULL,
    NULL,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static void
init_plugin (PurplePlugin * plugin)
{
}

PURPLE_INIT_PLUGIN (whatsapp_butler, init_plugin, info)
