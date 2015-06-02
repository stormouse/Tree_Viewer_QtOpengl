#ifndef TREEFILE
#define TREEFILE

#include <QDomDocument>
#include "objectfactory.h"
class TreeFile
{
private:
	QDomDocument doc;
	QString path;
public:
	void CreateDocument(QString back_path,ObjectFactory* trees)
	{
		doc.clear();
		doc.appendChild(doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\""));
		QDomElement root = doc.createElement("File");
		doc.appendChild(root);
		QDomElement background = doc.createElement("background");
		QDomText back_text = doc.createTextNode(back_path);
		background.appendChild(back_text);
		root.appendChild(background);

		QDomElement forest = doc.createElement("forest");
		const QMap<QString, Object*> * treemap = trees->Factory();
		QMap<QString, Object*>::ConstIterator it;
		for (it = treemap->begin(); it != treemap->end(); ++it)
		{
			QDomElement tree = doc.createElement("tree");

			QDomElement name = doc.createElement("name");
			QDomText name_text = doc.createTextNode(it.value()->GetName());
			name.appendChild(name_text);
			tree.appendChild(name);

			QDomElement modelname = doc.createElement("modelname");
			QDomText modelname_text = doc.createTextNode(it.value()->GetModelName());
			modelname.appendChild(modelname_text);
			tree.appendChild(modelname);

			QDomElement position = doc.createElement("position");
			QDomElement px = doc.createElement("x");
			QDomText px_text = doc.createTextNode(QString("%1").arg(it.value()->GetPosition().x()));
			px.appendChild(px_text);
			QDomElement py = doc.createElement("y");
			QDomText py_text = doc.createTextNode(QString("%1").arg(it.value()->GetPosition().y()));
			py.appendChild(py_text);
			QDomElement pz = doc.createElement("z");
			QDomText pz_text = doc.createTextNode(QString("%1").arg(it.value()->GetPosition().z()));
			pz.appendChild(pz_text);
			position.appendChild(px);
			position.appendChild(py);
			position.appendChild(pz);
			tree.appendChild(position);

			QDomElement angle = doc.createElement("angle");
			QDomElement ax = doc.createElement("x");
			QDomText ax_text = doc.createTextNode(QString("%1").arg(it.value()->GetEulerAngles().x()));
			ax.appendChild(ax_text);
			QDomElement ay = doc.createElement("y");
			QDomText ay_text = doc.createTextNode(QString("%1").arg(it.value()->GetEulerAngles().y()));
			ay.appendChild(ay_text);
			QDomElement az = doc.createElement("z");
			QDomText az_text = doc.createTextNode(QString("%1").arg(it.value()->GetEulerAngles().z()));
			az.appendChild(az_text);
			angle.appendChild(ax);
			angle.appendChild(ay);
			angle.appendChild(az);
			tree.appendChild(angle);

			QDomElement scale = doc.createElement("scale");
			QDomElement sx = doc.createElement("x");
			QDomText sx_text = doc.createTextNode(QString("%1").arg(it.value()->GetScale().x()));
			sx.appendChild(sx_text);
			QDomElement sy = doc.createElement("y");
			QDomText sy_text = doc.createTextNode(QString("%1").arg(it.value()->GetScale().y()));
			sy.appendChild(sy_text);
			QDomElement sz = doc.createElement("z");
			QDomText sz_text = doc.createTextNode(QString("%1").arg(it.value()->GetScale().z()));
			sz.appendChild(sz_text);
			scale.appendChild(sx);
			scale.appendChild(sy);
			scale.appendChild(sz);
			tree.appendChild(scale);

			forest.appendChild(tree);
		}
		root.appendChild(forest);

		QDomElement globalsetting = doc.createElement("globalsetting");
		root.appendChild(globalsetting);
	}

	void CreateXMLFile(QString filename)
	{
		QString xmlFileName = filename + ".xml";
		QFile file(xmlFileName);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QFile::Text))
		{
			qDebug() << xmlFileName;
			file.close();
			return;
		}
		QTextStream out(&file);
		out.setCodec("UTF-8");
		doc.save(out, 4, QDomNode::EncodingFromTextStream);
		file.close();
	}
};

#endif