void
clear(Monitor *m) {
	Client *c;
	for (c = m->cl->stack; c; c = c->snext) {
		if(ISVISIBLE(c, m)) {
			XMoveWindow(dpy, c->win, WIDTH(c) * -2, c->y);
		}
	}
}
