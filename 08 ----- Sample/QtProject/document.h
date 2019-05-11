#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "childframe.h"

#include <QObject>

class Document : public QObject
{
	Q_OBJECT

public:
	Document(ChildFrame *pframe) { this->pFrame = pframe; }
	virtual ~Document() { }

signals:
	void contentsChanged();

public:
	// public interface for document
	virtual bool loadFile(const QString &fileName) = 0;
	virtual bool saveFile(const QString &fileName) = 0;

	virtual bool isModified() = 0;
	virtual void setModified(bool m = true) = 0;

public:
    // public interface for document-view framework
    ChildFrame *frame() { return pFrame; }

protected:
	ChildFrame *pFrame;
};

#endif // DOCUMENT_H
