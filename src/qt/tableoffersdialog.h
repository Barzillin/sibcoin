#ifndef TABLEOFFERSDIALOG_H
#define TABLEOFFERSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include "guiutil.h"
#include "dex/dexdb.h"
#include "offermodel.h"
#include "tableofferdelegate.h"
#include "callbackdbforgui.h"

using namespace dex;

namespace Ui {
    class TableOffersDialog;
}

class TableOffersDialog : public QDialog
{
    Q_OBJECT

public:
    TableOffersDialog(DexDB *db, QDialog *parent = nullptr);
    virtual ~TableOffersDialog();

    void updateNavigationData();

protected:
    OfferModel *pModel;
    TableOfferDelegate *pDelegate;
    DexDB *db;
    CallBackDbForGui *callBack;

    virtual void resizeEvent(QResizeEvent *event);

    void init();
    QString currentCountry() const;
    QString currentCurrency() const;
    QString currentPayment() const;
    int currentOfferIndex() const;

    void useMyOfferMode(const bool &b);

private:
    Ui::TableOffersDialog *ui;
    GUIUtil::TableViewLastColumnResizingFixer *columnResizingFixer;

protected Q_SLOTS:
    virtual void openCreatorOffer();
    virtual void clickedButton(const int &index) = 0;
    virtual void updateTables(const TypeTable &table, const TypeTableOperation &operation, const StatusTableOperation &status);

private Q_SLOTS:
    void changedFilterCountryIso(const int &);
    void changedFilterCurrencyIso(const int &);
    void changedFilterPaymentMethod(const int &);
    void changedFilterOfferType(const int &);

Q_SIGNALS:
    void navigationDataUpdate();
    void dataChanged();
};

#endif
