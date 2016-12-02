#include "pileupeffect.h"

PileUpEffect::PileUpEffect()
{
}

const float SPEED = 1080 / 0.3f;

bool PileUpEffect::acceptsString(const InputString &inputString)
{
    return inputString.startsWith(4, SOT_WORD);
}

void PileUpEffect::transform(Text &t, float &time, Node &inputNode,
                             glm::vec3 startPos, glm::vec3 startRot,
                             glm::vec3 endPos, glm::vec3 endRot,
                             glm::vec3 scPos, glm::vec3 scRot)
{
    t.setPosition(startPos);
    t.setRotation(startRot);

    // Move/Rotate next to
    glm::vec3 delta = endPos - startPos;
    float dur = glm::length(delta) / SPEED;
    //float dur = 0.4;
    t.runAction(time, new MoveBy(dur, delta));
    t.runAction(time, new RotateTo(dur, endRot.x, endRot.y, endRot.z));
    time += dur;

    // Move/rotate scene
    dur = 0.3f;
    inputNode.runAction(time, new MoveTo(dur, scPos));
    inputNode.runAction(time, new RotateTo(dur, scRot.x, scRot.y, scRot.z));
    time += dur;
}

Text* PileUpEffect::newText(InputString &inputString,
                            Node &inputNode, float width, Point &td)
{
    auto t = new Text(toUpper(inputString.read(1, SOT_WORD)), "Roboto-Bold");
    inputNode.addChild(t);
    t->setLineLength(100000);
    t->setScaleForWidth(width);
    td = t->getDimensions();
    return t;
}

Text* PileUpEffect::newTextWithHeight(InputString &inputString,
                            Node &inputNode, float height, Point &td)
{
    auto t = new Text(toUpper(inputString.read(1, SOT_WORD)), "Roboto-Bold");
    inputNode.addChild(t);
    t->setLineLength(1000000);
    t->setScaleForHeight(height);
    td = t->getDimensions();
    return t;
}


float PileUpEffect::run(InputString &inputString, Node &inputNode, float startTime)
{
    float space = 30;

    inputNode.runAction(startTime,
        new MoveTo(0, glm::vec3(0, 0, 0))
    );

    float baseWidth = 1000;
    float trDur = 0.3;

    // vvv G2 vvv
    // vvv G1 vvv
    // Create new word
    auto t = new Text(toUpper(inputString.read(1, SOT_WORD)), "Roboto-Bold");
    inputNode.addChild(t);
    t->setAlpha(0);
    t->setScaleForWidth(baseWidth);
    Point td = t->getDimensions();
    glm::vec3 tp(1920 - baseWidth, 0, -600);
    t->setPosition(tp);

    // Fly to the scene
    t->runAction(startTime, new FadeIn(0.1));
    tp = {(1920 - baseWidth) / 2, (1080 - td.y) / 2, 0};
    t->runAction(startTime, new EaseIt(
        new MoveTo(trDur, tp)
    ));
    startTime += trDur;

    // ================

    Point t2d;
    Text *t2 = newText(inputString, inputNode, baseWidth, t2d);
    glm::vec3 t2p(tp.x, tp.y - space - t2d.y, 0);
    transform(*t2, startTime, inputNode,
              glm::vec3(tp.x, -t2d.y, 0), glm::vec3(0,0,0),
              t2p, glm::vec3(0,0,0),
              glm::vec3(0, (td.y + t2d.y) / 2 + space, 0), glm::vec3(0,0,0));

    Point t3d;
    Text *t3 = newText(inputString, inputNode, td.y + space + t2d.y, t3d);
    glm::vec3 t3p(tp.x+td.x+space+t3d.y, t2p.y, 0);
    transform(*t3, startTime, inputNode,
              glm::vec3(1920+t3d.y, t2p.y, 0), glm::vec3(0,0,-90),
              t3p, glm::vec3(0,0,-90),
              glm::vec3(-t2p.y + (1920 - t3d.x) / 2, t3p.x + (1080 - t3d.y) / 2, 0), glm::vec3(0,0, 90));

    Point t4d;
    Text *t4 = newText(inputString, inputNode, t3d.x, t4d);
    glm::vec3 t4p(t3p.x+space+t4d.y, t3p.y, 0);
    transform(*t4, startTime, inputNode,
              glm::vec3(t3p.x+1080/2+t4d.y, t4p.y, 0), glm::vec3(0,0,-90),
              t4p, glm::vec3(0,0,-90),
              glm::vec3(-t3p.y + (1920 - t4d.x) / 2, t4p.x + (1080 - t4d.y) / 2, 0), glm::vec3(0,0, 90));

    // Right column
    float lineHeight = (tp.x + 3*space + t3d.y + t4d.y) / 3 - space;

    float zoomStartTime = startTime;

    float maxWidth = 0;
    for (int i = 0; i < 3; ++i) {
        Point t5d;
        Text *t5 = newTextWithHeight(inputString, inputNode, lineHeight, t5d);
        if (t5d.x > maxWidth)
            maxWidth = t5d.x;
        t5->setRotation(glm::vec3(0,0,-90));
        t5->setPosition(tp.x + t5d.y + i * (t5d.y + space), t3p.y + (t3d.x+1920)/2, 0);

        t5->runAction(startTime, new MoveTo(0.3f, glm::vec3(tp.x+t5d.y, tp.y+td.y+space, 0)));
        startTime += 0.15;
        if (i == 0) {
            t->runAction(startTime, new MoveBy(0.15, glm::vec3(0, -2500, 0)));
            t2->runAction(startTime, new MoveBy(0.15, glm::vec3(0, -2500, 0)));
        } else if (i == 1) {
            t3->runAction(startTime, new MoveBy(0.15, glm::vec3(0, -2500, 0)));
        } else if (i == 2) {
            t4->runAction(startTime, new MoveBy(0.15, glm::vec3(0, -2500, 0)));
        }
        startTime += 0.15;
    }

    float totalWidth = t2d.y + tp.y + maxWidth + 2*space + 150;
    float widthScale = 1920 / totalWidth;
    float totalHeight = t2d.x + t3d.y + t4d.y + 2*space + 150;
    float heightScale = 1080 / totalHeight;

    inputNode.runAction(zoomStartTime, new ScaleTo(0.3f, glm::max(widthScale, heightScale)));
    inputNode.runAction(zoomStartTime, new MoveTo(0.3f, glm::vec3(0, 1920, 0)));

    // Clean everything

    startTime += 1;

    inputNode.runAction(startTime,
        new MoveTo(0, glm::vec3(-1920, 0, 0))
    );

    return startTime;
}
