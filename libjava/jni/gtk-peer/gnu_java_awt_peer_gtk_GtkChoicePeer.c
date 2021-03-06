/* gtkchoicepeer.c -- Native implementation of GtkChoicePeer
   Copyright (C) 1998, 1999 Free Software Foundation, Inc.

This file is part of GNU Classpath.

GNU Classpath is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Classpath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Classpath; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA.

Linking this library statically or dynamically with other modules is
making a combined work based on this library.  Thus, the terms and
conditions of the GNU General Public License cover the whole
combination.

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent
modules, and to copy and distribute the resulting executable under
terms of your choice, provided that you also meet, for each linked
independent module, the terms and conditions of the license of that
module.  An independent module is a module which is not derived from
or based on this library.  If you modify this library, you may extend
this exception to your version of the library, but you are not
obligated to do so.  If you do not wish to do so, delete this
exception statement from your version. */


#include "gtkpeer.h"
#include "gnu_java_awt_peer_gtk_GtkChoicePeer.h"

static void selection_changed (GtkComboBox *combobox, jobject peer);

JNIEXPORT void JNICALL 
Java_gnu_java_awt_peer_gtk_GtkChoicePeer_create 
  (JNIEnv *env, jobject obj)
{
  GtkWidget *combobox;
  jobject *gref;

  NSA_SET_GLOBAL_REF (env, obj);
  gref = NSA_GET_GLOBAL_REF (env, obj);

  gdk_threads_enter ();
  
  combobox = gtk_combo_box_new_text ();

  g_signal_connect (combobox, "changed",
                    G_CALLBACK (selection_changed), *gref);

  gdk_threads_leave ();

  NSA_SET_PTR (env, obj, combobox);
}

JNIEXPORT void JNICALL 
Java_gnu_java_awt_peer_gtk_GtkChoicePeer_append 
  (JNIEnv *env, jobject obj, jobjectArray items)
{
  gpointer ptr;
  jsize count, i;

  ptr = NSA_GET_PTR (env, obj);

  gdk_threads_enter ();

  count = (*env)->GetArrayLength (env, items);

  for (i = 0; i < count; i++) 
    {
      jobject item;
      const char *label;

      item = (*env)->GetObjectArrayElement (env, items, i);
      label = (*env)->GetStringUTFChars (env, item, NULL);

      gtk_combo_box_append_text (GTK_COMBO_BOX (ptr), label);

      (*env)->ReleaseStringUTFChars (env, item, label);
    }

  gdk_threads_leave ();
}

JNIEXPORT void JNICALL 
Java_gnu_java_awt_peer_gtk_GtkChoicePeer_nativeAdd 
  (JNIEnv *env, jobject obj, jstring item, jint index)
{
  void *ptr;
  const char *label;

  ptr = NSA_GET_PTR (env, obj);
  
  label = (*env)->GetStringUTFChars (env, item, 0);      

  gdk_threads_enter ();
  gtk_combo_box_insert_text (GTK_COMBO_BOX (ptr), index, label);
  gdk_threads_leave ();

  (*env)->ReleaseStringUTFChars (env, item, label);
}

JNIEXPORT void JNICALL 
Java_gnu_java_awt_peer_gtk_GtkChoicePeer_nativeRemove 
  (JNIEnv *env, jobject obj, jint index)
{
  void *ptr;

  ptr = NSA_GET_PTR (env, obj);

  gdk_threads_enter ();
  gtk_combo_box_remove_text (GTK_COMBO_BOX (ptr), index);
  gdk_threads_leave ();
}

JNIEXPORT void JNICALL 
Java_gnu_java_awt_peer_gtk_GtkChoicePeer_nativeRemoveAll 
  (JNIEnv *env, jobject obj)
{
  void *ptr;
  GtkTreeModel *model;
  gint count, i;

  ptr = NSA_GET_PTR (env, obj);

  gdk_threads_enter ();

  model = gtk_combo_box_get_model (GTK_COMBO_BOX (ptr));
  count = gtk_tree_model_iter_n_children (model, NULL);

  /* First, unselect everything, to avoid problems when removing items. */
  gtk_combo_box_set_active (GTK_COMBO_BOX (ptr), -1);

  for (i = count - 1; i >= 0; i--) {
    gtk_combo_box_remove_text (GTK_COMBO_BOX (ptr), i);
  }

  gdk_threads_leave ();
}

JNIEXPORT void JNICALL 
Java_gnu_java_awt_peer_gtk_GtkChoicePeer_select 
  (JNIEnv *env, jobject obj, jint index)
{
  void *ptr;

  ptr = NSA_GET_PTR (env, obj);

  gdk_threads_enter ();
  gtk_combo_box_set_active (GTK_COMBO_BOX (ptr), index);
  gdk_threads_leave ();
}

JNIEXPORT jint JNICALL 
Java_gnu_java_awt_peer_gtk_GtkChoicePeer_nativeGetSelected 
  (JNIEnv *env, jobject obj)
{
  void *ptr;
  int index;

  ptr = NSA_GET_PTR (env, obj);

  gdk_threads_enter ();
  index = gtk_combo_box_get_active (GTK_COMBO_BOX (ptr));
  gdk_threads_leave ();

  return index;
}

static void selection_changed (GtkComboBox *combobox, jobject peer)
{
  jstring label;
  GtkTreeModel *model;
  GtkTreeIter iter;
  gchar *selected;
  gint index;

  index = gtk_combo_box_get_active(combobox);

  if (index >= 0)
    {
      model = gtk_combo_box_get_model (combobox);

      gtk_combo_box_get_active_iter (combobox, &iter);

      gtk_tree_model_get (model, &iter, 0, &selected, -1);

      gdk_threads_leave ();

      label = (*gdk_env())->NewStringUTF (gdk_env(), selected);
      (*gdk_env())->CallVoidMethod (gdk_env(), peer,
			          choicePostItemEventID,
			          label,
			          (jint) AWT_ITEM_SELECTED);
      gdk_threads_enter ();
    }
}
