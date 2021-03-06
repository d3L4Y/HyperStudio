/*
 * Copyright 2007-2009 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the GPL v3 License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#include <Alert.h>
#include <Font.h>
#include <String.h>
#include <TextView.h>

#include <stdarg.h>
#include <time.h>

#include "AboutWindow.h"

AboutWindow::AboutWindow(char* appName, int32 firstCopyrightYear,
	const char** authors, char* extraInfo)
{
	fAppName = new BString(appName);
	fText = new BString();

	// Get current year
	time_t tp;
	time(&tp);
	char currentYear[5];
	strftime(currentYear, 5, "%Y", localtime(&tp));

	// Build the text to display
	BString text(appName);
	text << "\n\nCopyright " B_UTF8_COPYRIGHT " ";
	text << firstCopyrightYear << "-" << currentYear << " Pier Luigi Fiorini.\n\n";
	text << "Written by:\n";
	for (int32 i = 0; authors[i]; i++)
		text << "    " << authors[i] << "\n";

	// The extra information is optional
	if (extraInfo != NULL)
		text << "\n" << extraInfo << "\n";

	fText->Adopt(text);
}


AboutWindow::~AboutWindow()
{
	delete fText;
}


void
AboutWindow::Show()
{
	BAlert *alert = new BAlert("About...", fText->String(), "Close");
	BTextView *view = alert->TextView();
	BFont font;
	view->SetStylable(true);
	view->GetFont(&font);
	font.SetFace(B_BOLD_FACE);
	font.SetSize(font.Size() * 1.7f);
	view->SetFontAndColor(0, fAppName->Length(), &font);
	alert->Go();
}
