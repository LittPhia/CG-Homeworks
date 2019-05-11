#ifndef CHILDFRAME_H
#define CHILDFRAME_H

#include <QWidget>

class View; 
class Document;
class MainWindow;

class ChildFrame : public QWidget
{
    Q_OBJECT

public:
    ChildFrame(MainWindow *pmain = 0);
	~ChildFrame();

public:
	// interface for main window
	void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();

public:
	// properties
	QSize sizeHint() const;
    QString currentFile() { return curFile; }

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void documentWasModified();

private:
	// members variables and functions
    QString curFile;
    bool isUntitled;
    QAction *action;

	bool okToContinue();
	void setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);

public:
	// public interface for document-view framework
	Document *document() { return pDoc; }
	View *view() { return pView; }
	MainWindow *main() { return pMain; }

private:
	// member variables for document-view framework
	Document *pDoc;
	View *pView;
	MainWindow *pMain;
};

#endif // CHILDFRAME_H
