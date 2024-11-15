static void killthis(Client *c);
static void bulkill(const Arg *arg);

void
killthis(Client *c) {
	if (!sendevent(c, wmatom[WMDelete])) {
		XGrabServer(dpy);
		XSetErrorHandler(xerrordummy);
		XSetCloseDownMode(dpy, DestroyAll);
		XKillClient(dpy, c->win);
		XSync(dpy, False);
		XSetErrorHandler(xerror);
		XUngrabServer(dpy);
	}
}

void
bulkill(const Arg *arg)
{
    Client *c;

	if (!selmon->sel)
		return;

    if (!arg->ui || arg->ui == 0) {
        killthis(selmon->sel);
        return;
    }

    for (c = selmon->clients; c; c = c->next) {
        if (!ISVISIBLE(c) || (arg->ui == 1 && c == selmon->sel))
            continue;
        killthis(c);
    }
}