/*
 * Copyright 2016 CodiLime
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef TRIGRAM_H
#define TRIGRAM_H

#include "visualisation/ngram.h"

#include <stdint.h>

#include <vector>

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QBasicTimer>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>

#include "visualisation/base.h"

namespace veles {
namespace visualisation {

class NGramWidget : public VisualisationWidget {
  Q_OBJECT

 public:
  enum class EVisualisationShape {CUBE, CYLINDER, SPHERE};

  explicit NGramWidget(QWidget *parent = 0);
  ~NGramWidget();

  bool prepareOptionsPanel(QBoxLayout *layout) override;

 public slots:
  void brightnessSliderMoved(int value);

 protected:
  void refresh() override;
  void initializeVisualisationGL() override;

  void timerEvent(QTimerEvent *e) override;

  void resizeGL(int w, int h) override;

  void keyPressEvent(QKeyEvent *) override;
  void keyReleaseEvent(QKeyEvent *) override;

  //void mouseMoveEvent(QMouseEvent *) override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;

  void paintGL() override;

  void initShaders();
  void initTextures();
  void initGeometry();

 private slots:
  void centerView();
  void playPause();
  void setFlat(bool);
  void setLayeredX(bool);
  void setLayeredZ(bool);
  void setShape(EVisualisationShape shape);
  void setUseBrightnessHeuristic(int state);

 private:
  void setBrightness(int value);
  int suggestBrightness(); // heuristic
  void autoSetBrightness();

  QBasicTimer timer;
  QOpenGLShaderProgram program;
  QOpenGLTexture *texture;
  QOpenGLBuffer *databuf;

  QOpenGLVertexArrayObject vao;
  float c_sph, c_cyl, c_brightness;
  float c_flat, c_layered_x, c_layered_z;

  bool cam_targeting;
  QVector3D cam_target;
  bool cam_target_rot;

  bool mode_flat_, mode_layered_x_, mode_layered_z_;

  QPushButton *mode_flat_pushbutton_;
  QPushButton *mode_layered_x_pushbutton_;
  QPushButton *mode_layered_z_pushbutton_;

  int width, height;
  EVisualisationShape shape_;
  int brightness_;

  QMatrix4x4 perspective;

  QQuaternion rotation;
  QVector3D rotationAxis;
  float angularSpeed;
  QVector2D mousePressPosition;

  QVector3D position, movement, speed;

  QPushButton *pause_button_, *center_button_;
  QPushButton *cube_button_, *cylinder_button_, *sphere_button_;
  QSlider *brightness_slider_;
  QCheckBox *use_heuristic_checkbox_;
  bool is_playing_, use_brightness_heuristic_;
};

}  // namespace visualisation
}  // namespace veles

#endif
