#include "childframe.h"

#include "meshview.h"
#include "mainwindow.h"
#include "meshdocument.h"

#include <QFileInfo>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDesktopWidget>

ChildFrame::ChildFrame(MainWindow *pmain /* = 0 */)
    : QWidget(pmain)
{
	pMain = pmain;

	// setup action for active sub window 
    action = new QAction(this);
    action->setCheckable(true);
    connect(action, SIGNAL(triggered()), this, SLOT(show()));
    connect(action, SIGNAL(triggered()), this, SLOT(setFocus()));

	// setup appearance and WA_DeleteOnClose attribute
	isUntitled = true;
	setWindowIcon(QPixmap(":/images/document.png"));
    setWindowTitle("[*]");
    setAttribute(Qt::WA_DeleteOnClose);

	// allocate document and view objects
	pDoc = new MeshDocument(this);
	pView = new MeshView(this);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(pView);
	layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);

	connect(document(), SIGNAL(contentsChanged()),
		this, SLOT(documentWasModified()));
}

ChildFrame::~ChildFrame()
{
	// deallocate document and view objects
	if (pDoc != NULL)
		delete pDoc;

	if (pView != NULL)
		delete pView;
}

void ChildFrame::newFile()
{
	// new file
    static int documentNumber = 1;

    curFile = tr("document%1.txt").arg(documentNumber);
    setWindowTitle(curFile + "[*]");
    action->setText(curFile);
    isUntitled = true;
    ++documentNumber;
}

bool ChildFrame::loadFile(const QString &fileName)
{
	// load file
	Document *doc = document();
	if (okToContinue() && doc->loadFile(fileName))
	{
		setCurrentFile(fileName);
		return true;
	}
	else
	    return false;
}

bool ChildFrame::save()
{
	// save file
    if (isUntitled) 
	{
        return saveAs();
    } 
	else 
	{
		Document *doc = document();
        return doc->saveFile(curFile);
    }
}

bool ChildFrame::saveAs()
{
	// save as file
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), curFile);
    if (fileName.isEmpty())
        return false;

	Document *doc = document();
    return doc->saveFile(fileName);
}

QSize ChildFrame::sizeHint() const
{
	// return preferred window size of child frame
	QDesktopWidget desktop;
	return QSize(desktop.availableGeometry().width(), desktop.availableGeometry().height());
}

void ChildFrame::closeEvent(QCloseEvent *event)
{
	// implementation of close Event
    if (okToContinue()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void ChildFrame::documentWasModified()
{
	// tag document modified
    setWindowModified(true);
}

bool ChildFrame::okToContinue()
{
	// remind user to save changes 
	if (document()->isModified()) 
	{
		int r = QMessageBox::warning(this, tr("MDI Editor"),
			tr("File %1 has been modified.\n"
			"Do you want to save your changes?")
			.arg(strippedName(curFile)),
			QMessageBox::Yes | QMessageBox::No
			| QMessageBox::Cancel);
		if (r == QMessageBox::Yes) 
		{
			return save();
		} 
		else if (r == QMessageBox::Cancel) 
		{
			return false;
		}
	}
	return true;
}

void ChildFrame::setCurrentFile(const QString &fileName)
{
	// set current file name
    curFile = fileName;
    isUntitled = false;
    action->setText(strippedName(curFile));
    document()->setModified(false);

	// set windows title
    setWindowTitle(strippedName(curFile) + "[*]");
    setWindowModified(false);
}

QString ChildFrame::strippedName(const QString &fullFileName)
{
	// return stripped file name
    return QFileInfo(fullFileName).fileName();
}
