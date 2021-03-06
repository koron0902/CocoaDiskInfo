#ifndef COCOA_DISK_INFO_GUI_DEVICE_H_
#define COCOA_DISK_INFO_GUI_DEVICE_H_

#include <gtkmm.h>
#include <gtkmm/widget.h>
#include "diskinfo/smart/atasmart.h"

namespace DiskInfo {
namespace GUI {
class Device {
  SMART::ATASMART smart_;

  class treeModel : public Gtk::TreeModel::ColumnRecord {
  public:
    treeModel() {
      add(state_);
      add(id_);
      add(name_);
      add(current_);
      add(worst_);
      add(threshold_);
      add(raw_);
    }

    Gtk::TreeModelColumn<Glib::ustring> state() const {
      return state_;
    };
    Gtk::TreeModelColumn<uint64_t> id() const {
      return id_;
    };
    Gtk::TreeModelColumn<Glib::ustring> name() const {
      return name_;
    };
    Gtk::TreeModelColumn<uint64_t> current() const {
      return current_;
    };
    Gtk::TreeModelColumn<uint64_t> worst() const {
      return worst_;
    };
    Gtk::TreeModelColumn<uint64_t> threshold() const {
      return threshold_;
    };
    Gtk::TreeModelColumn<Glib::ustring> raw() const {
      return raw_;
    };

  private:
    Gtk::TreeModelColumn<Glib::ustring> state_;
    Gtk::TreeModelColumn<uint64_t> id_;
    Gtk::TreeModelColumn<Glib::ustring> name_;
    Gtk::TreeModelColumn<uint64_t> current_;
    Gtk::TreeModelColumn<uint64_t> worst_;
    Gtk::TreeModelColumn<uint64_t> threshold_;
    Gtk::TreeModelColumn<Glib::ustring> raw_;
  };

  class labeldText {
  public:
    labeldText() = default;
    labeldText(const std::string _label, const std::string _text) {
      label_   = Gtk::Label(_label);
      textBuf_ = text_.get_buffer();
      textBuf_->set_text(_text);
      text_.set_editable(false);
    }

    Gtk::HBox& Build() {
      box_.pack_start(label_, Gtk::PACK_SHRINK, 4);
      box_.pack_start(text_, Gtk::PACK_SHRINK, 4);
      return box_;
    }

  private:
    Gtk::Label label_;
    Gtk::TextView text_;
    Glib::RefPtr<Gtk::TextBuffer> textBuf_;
    Gtk::HBox box_;
  };

  treeModel model_;
  Gtk::TreeView tree_;
  Glib::RefPtr<Gtk::TreeStore> treeStore_;
  Gtk::Frame info_, state_;
  labeldText devModel_, devSerial_, devPowerOnTime_, devPowerOnCount_, devCapacity_,
      devTemperature_;
  Gtk::HBox page_;
  Gtk::VBox infoBox_, stateBox_, dev_;

public:
  Device() = default;
  Device(DiskInfo::SMART::ATASMART _smart);
  Gtk::HBox& Build();
  void CreateTree();
  void CreateInfo();
};
} // namespace GUI
} // namespace DiskInfo

#endif
