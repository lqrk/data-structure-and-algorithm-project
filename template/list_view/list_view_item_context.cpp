#include "list_view_item_context.h"

ListViewItemContext NewListViewItemContext(
  size_tp width = LIST_VIEW_ITEM_WIDTH,
  size_tp height = LIST_VIEW_ITEM_HEIGHT,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = LIST_VIEW_ITEM_FOREGROUND,
  color_tp background = LIST_VIEW_ITEM_BACKGROUND,
  color_tp active_foreground = LIST_VIEW_ITEM_ACTIVE_FOREGROUND,
  color_tp active_background = LIST_VIEW_ITEM_ACTIVE_BACKGROUND,
  bool (* console)(char) = STANDARD_CONSOLE,
  void * data = NULL
) {
  ListViewItemContext list_view_item_context = (ListViewItemContext) malloc(sizeof(ListViewItemContextT));

  list_view_item_context->position_x = position_x;
  list_view_item_context->position_y = position_y;
  list_view_item_context->width = width;
  list_view_item_context->height = height;
  list_view_item_context->foreground = foreground;
  list_view_item_context->background = background;
  list_view_item_context->active_foreground = active_foreground;
  list_view_item_context->active_background = active_background;
  list_view_item_context->console = console;
  list_view_item_context->data = data;

  return list_view_item_context;
}

void DestroyListViewItemContext(ListViewItemContext &list_view_item_context) {
  free(list_view_item_context);
  list_view_item_context = NULL;
}

void RenderListViewItemWithDataAsString(
  ListViewItemContext list_view_item_context,
  status_tp status = NORMAL_LIST_VIEW_ITEM
) {
  color_tp foreground = list_view_item_context->foreground;
  color_tp background = list_view_item_context->background;

  if (status == ACTIVE_LIST_VIEW_ITEM) {
    foreground = list_view_item_context->active_foreground;
    background = list_view_item_context->active_background;
  }

  DrawRecShape(
    list_view_item_context->width,
    list_view_item_context->height,
    ' ',
    list_view_item_context->position_x,
    list_view_item_context->position_y,
    foreground,
    background
  );

  str_tp text = (str_tp) (list_view_item_context->data);
  size_tp position_x = list_view_item_context->position_x + (list_view_item_context->width - strlen(text)) / 2;
  position_x = position_x >= 0 ? position_x : 0;

  position_x = list_view_item_context->position_x + 2;

  size_tp position_y = list_view_item_context->position_y + list_view_item_context->height / 2;
  WriteStr(
    text,
    position_x,
    position_y,
    foreground,
    background
  );
}

keycode_tp ActiveListViewItemWithDataAsString(ListViewItemContext list_view_item_context) {
  RenderListViewItemWithDataAsString(list_view_item_context, ACTIVE_LIST_VIEW_ITEM);

  if (list_view_item_context->console != NULL) {
    char c;
    do {
      c = Console();
    } while (!list_view_item_context->console(c));

    return c;
  }

  return NULL_KEY;
}
